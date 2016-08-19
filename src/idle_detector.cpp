#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

#include "idle_detector.hpp"
#include "trace_data.hpp"
#include <otf2/otf2.h>
 


IdleDetector::IdleDetector(TraceData * trace_data, double interval_sec, uint64_t length_threshold, uint64_t occupancy_threshold)
        : trace_data(trace_data), interval_sec(interval_sec), length_threshold(length_threshold), occupancy_threshold(occupancy_threshold)  {
    setup();
}


IdleDetector::~IdleDetector() {

}


void IdleDetector::setup() {
    if(trace_data == nullptr) {
        return;
    }

    const double resolution = (double)trace_data->get_timer_resolution(); // Ticks per sec
    const double length = (double)trace_data->get_trace_length();
    const double offset = (double)trace_data->get_global_offset();
    interval = resolution * interval_sec;
    start = offset;
    end = offset + length;
    num_samples = (uint64_t)std::round(length/interval);

    std::cerr << "num samples: " << num_samples << std::endl;

    occupancy.clear();
    occupancy.reserve(num_samples);
    occupancy.insert(occupancy.begin(), num_samples, 0);
}


void IdleDetector::analyze() {
    if(trace_data == nullptr) {
        return;
    }

    // Get occupancy for each sample point for each location
    const OTF2_LocationRef num_locs = trace_data->get_locations().size();
    for(OTF2_LocationRef loc = 0; loc < num_locs; ++loc) {
        double current_time = start;
        for(uint64_t sample = 0; sample < num_samples; ++sample) {
            TraceData::maybe_event_pair_t task = 
                trace_data->get_task_at_time(loc, (OTF2_TimeStamp)std::round(current_time));
            if(task) {
                // There is a task running at current_time
                uint64_t & s = occupancy[sample];
                ++s;
                if(s > max_occupancy) {
                    max_occupancy = s;
                }
            }
            current_time += interval;
        }
    }

    {
        // Find candidate end samples with occupancy less than threshold
        std::vector<uint64_t> candidate_ends;
        for(uint64_t sample = 1; sample < num_samples-1; ++sample) {
            if(occupancy[sample] < occupancy_threshold && occupancy[sample+1] >= occupancy_threshold) {
                candidate_ends.push_back(sample);    
            }
        }

        idle_region_list_t candidate_regions;
        // From each candidate end, scan back to full occupancy
        for(const uint64_t candidate_end : candidate_ends) {
            uint64_t candidate_start;
            for(candidate_start = candidate_end; candidate_start >= 1; --candidate_start) {
                if(occupancy[candidate_start] == max_occupancy) {
                    break;
                }
            }
            if(candidate_start != 0 && candidate_end - candidate_start >= length_threshold) {
                // This is a candidate
                // Scan forward to find next full occupancy
                uint64_t next_full;
                for(next_full = candidate_end; next_full < num_samples; ++next_full) {
                    if(occupancy[next_full] == max_occupancy) {
                        break;
                    }
                }
                candidate_regions.push_back(std::make_tuple(candidate_start, candidate_end, next_full, occupancy[candidate_start], occupancy[candidate_end], occupancy[next_full]));
            }
        }

        const uint64_t num_candidates = candidate_regions.size();
        for(uint64_t candidate = 0; candidate < num_candidates - 1; ++candidate) {
            const uint64_t my_start = std::get<0>(candidate_regions[candidate]);
            const uint64_t next_start = std::get<0>(candidate_regions[candidate+1]);
            if(my_start != next_start) {
                idle_regions.push_back(candidate_regions[candidate]);        
                const uint64_t my_end = std::get<1>(candidate_regions[candidate]);
                starved_time += (my_end - my_start) * interval_sec;
            }
        }
        // Last region
        idle_regions.push_back(candidate_regions[num_candidates-1]);
    }

    // Now we have all the idle regions
    for(const region_t & region : idle_regions) {
        const uint64_t region_end = std::get<1>(region);
        const uint64_t rel_time = (uint64_t)std::round(region_end * interval);
        const uint64_t offset = trace_data->get_global_offset();
        // Global time is the trace timestamp of the end of the idle region
        const uint64_t global_time = offset + rel_time;
        const uint64_t next_full_occ_time = std::get<2>(region);
        const uint64_t rel_next_full_occ_time = (uint64_t)std::round(next_full_occ_time * interval);
        const uint64_t last_time = offset + rel_next_full_occ_time;
        // Scan forward in the trace to find the earliest time
        // after the idle region where multiple events are running
        uint64_t candidate_time = global_time;
        const TraceData::Event * end_event = nullptr;
        uint64_t tasks_running = 0;
        while(tasks_running < 2 && candidate_time < last_time) {
            // Check how many tasks are running at candidate_time
            tasks_running = 0;
            uint64_t earliest_next_time = std::numeric_limits<uint64_t>::max();
            const TraceData::Event * candidate_event = nullptr;
            for(uint64_t loc = 0; loc < num_locs; ++loc) {
                TraceData::maybe_event_iter_pair_t task = 
                    trace_data->get_task_iter_at_time(loc, candidate_time, true);
                if(task) {
                    // Is this task running?
                    const uint64_t this_start = task->first->get_time();
                    const uint64_t this_end   = task->second->get_time();
                    if(this_start <= candidate_time && this_end >= candidate_time) {
                        ++tasks_running;
                        candidate_event = &(*(task->first));
                    } else if(this_start > candidate_time){
                        // If this task isn't running, then use its start time
                        // as a potential next event start time.
                        if(this_start < earliest_next_time ) {
                            earliest_next_time = this_start;
                        }
                    } 
                    // Get the start time of the next event
                    TraceData::event_list_t::const_iterator next = 
                        trace_data->get_next_compute_event(loc, task->second);
                    const uint64_t next_time = next->get_time();
                    if(next_time < earliest_next_time) {
                        earliest_next_time = next_time;
                    }
                } else {
                    std::cerr << "No task at time " << candidate_time << "?" << std::endl;
                }
            }
            if(tasks_running == 1) {
                end_event = candidate_event;
            }
            if(earliest_next_time == std::numeric_limits<uint64_t>::max()) {
                std::cerr << "ERROR: earliest_next_time should have changed." << std::endl;
                abort();
            }
            if(earliest_next_time == candidate_time) {
                std::cerr << "ERROR: candidate_time should have changed." << std::endl;
                abort();
            }
            candidate_time = earliest_next_time + 1;
        }
        if(end_event == nullptr) {
            std::cerr << "ERROR: end_event should not be null." << std::endl;
        } else {
            if(end_event->get_time() > last_time) {
                std::cerr << "End event should not occur after next full occupancy!" << std::endl;
            }
            region_end_events.push_back(end_event);
        }
    }
    std::cerr << std::endl;



}

std::string IdleDetector::get_report() {
    std::stringstream ss;
    
    /*
    ss << std::setw(8) << "Sample" << " ";
    ss << std::setw(10) << "Occupancy\n";
    uint64_t sample_num = 0;
    for(auto sample : occupancy) {
        ss << std::setw(8) << sample_num << " ";
        ss << std::setw(10) << sample << "\n";
        ++sample_num;
    }
    ss << std::setw(8) << "max" << " ";
    ss << std::setw(10) << max_occupancy;
    ss << "\n\n";
    */

    ss << std::setw(10) << std::left << "Region" << " ";
    ss << std::setw(10) << std::left << "Start" << " ";
    ss << std::setw(10) << std::left << "End" << " ";
    ss << std::setw(10) << std::left << "Length" << " ";
    //ss << std::setw(10) << "Next" << " ";
    ss << std::setw(10) << std::left << "Start Occ" << " ";
    ss << std::setw(10) << std::left << "End Occ" << " ";
    ss << std::setw(15) << std::left << "Breaking Task" << " ";
    ss << std::setw(15) << std::left << "GUID" << "\n";
    uint64_t region_num = 0;
    for(auto region : idle_regions) {
        const double start =  (std::get<0>(region) * interval_sec);
        const double end =  (std::get<1>(region) * interval_sec);
        const double len = end - start;
        //const double next = (std::get<2>(region) * interval_sec);
        const std::string name = region_end_events[region_num]->get_object().get_name();
        const std::string guid = region_end_events[region_num]->get_object().get_guid();
        ss << std::setw(10) << std::right << region_num << " ";
        ss << std::setw(10) << std::right << std::fixed << std::setprecision(3) << start << " ";
        ss << std::setw(10) << std::right << std::fixed << std::setprecision(3) << end << " ";
        ss << std::setw(10) << std::right << std::fixed << std::setprecision(3) << len << " ";
        //ss << std::setw(10) << std::fixed << std::setprecision(3) << next << " ";
        ss << std::setw(10) << std::right << std::get<3>(region) << " ";
        ss << std::setw(10) << std::right << std::get<4>(region) << " ";
        ss << std::setw(15) << std::left << name << " ";
        ss << std::setw(15) << std::left << guid << "\n";
        ++region_num;
    }

    ss << "\n";
    ss << std::setw(10) << "Starved:" << " ";
    ss << std::setw(10) << starved_time << " ";

    ss << std::endl;

    return ss.str();
}

void IdleDetector::set_trace_data(TraceData * trace_data) {
   this->trace_data = trace_data;
   setup();
}

