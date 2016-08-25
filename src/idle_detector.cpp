#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

#include "idle_detector.hpp"
#include "trace_data.hpp"
#include "utils.hpp"

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

    occupancy.clear();
    occupancy.reserve(num_samples);
    occupancy.insert(occupancy.begin(), num_samples, 0);
}

void IdleDetector::calculate_occupancy() {
    // Get occupancy for each sample point for each location
    for(OTF2_LocationRef loc : trace_data->get_location_refs()) {
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
}

void IdleDetector::find_idle_regions() {
    uint64_t region_num = 0;
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
            //std::cerr << std::setw(10) << std::right << region_num << " ";
            //std::cerr << std::setw(11) << std::right << candidate_start << " ";
            //std::cerr << std::setw(11) << std::right << candidate_end << " ";
            //std::cerr << std::setw(10) << std::right << next_full << " ";
            //std::cerr << std::setw(10) << std::right << occupancy[candidate_start] << " ";
            //std::cerr << std::setw(10) << std::right << occupancy[candidate_end] << " ";
            //std::cerr << std::setw(10) << std::right << occupancy[next_full] << "\n";
            ++region_num;
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

void IdleDetector::find_region_boundary_events(const bool forward, const bool less_than, const bool from_start, const uint64_t threshold, IdleDetector::event_list_t & list) {
    if(!forward && from_start) {
        std::cerr << "ERROR: Scanning backwards from the start doesn't make sense." << std::endl;
        throw std::invalid_argument("!forward && from_start");
    }
    uint64_t region_num = 0;
    for(const region_t & region : idle_regions) {
        //std::cerr << "Processing region " << region_num << std::endl;
        const uint64_t region_end = std::get<1>(region);
        const uint64_t rel_time = (uint64_t)std::round(region_end * interval);
        const uint64_t offset = trace_data->get_global_offset();
        // Global time is the trace timestamp of the end of the idle region
        const uint64_t global_time = offset + rel_time;
        const uint64_t next_full_occ_time = std::get<2>(region);
        const uint64_t rel_next_full_occ_time = (uint64_t)std::round(next_full_occ_time * interval);
        // Time marking the return to full occupancy after the idle region
        const uint64_t last_time = offset + rel_next_full_occ_time;
        const uint64_t prev_full_occ_time = std::get<0>(region);
        const uint64_t rel_prev_full_occ_time = (uint64_t)std::round(prev_full_occ_time * interval);
        // Time marking the last full occupancy before the idle region
        const uint64_t first_time = offset + rel_prev_full_occ_time;
        // Scan forward or backwards in the trace to find the earliest time
        // after the idle region or latest time within the idle region
        // where multiple events are running
        uint64_t candidate_time = from_start ? first_time : global_time;
        const TraceData::Event * end_event = nullptr;
        uint64_t tasks_running = less_than ? std::numeric_limits<uint64_t>::min() : std::numeric_limits<uint64_t>::max();
        while( ((less_than && tasks_running < threshold) || (!less_than && tasks_running >= threshold))
                && candidate_time <= last_time && candidate_time >= first_time) {
            // Check how many tasks are running at candidate_time
            tasks_running = 0;
            uint64_t candidate_next_time = forward ? std::numeric_limits<uint64_t>::max() : std::numeric_limits<uint64_t>::min();
            const TraceData::Event * candidate_event = nullptr;
            for(OTF2_LocationRef loc : trace_data->get_location_refs()) {
                TraceData::maybe_event_iter_pair_t task = 
                    trace_data->get_task_iter_at_time(loc, candidate_time, true);
                if(task) {
                    // Is this task running?
                    const uint64_t this_start = task->first->get_time();
                    const uint64_t this_end   = task->second->get_time();
                    if(this_start <= candidate_time && this_end >= candidate_time) {
                        ++tasks_running;
                        candidate_event = &(*(task->first));
                    } else if(forward && this_start > candidate_time) {
                        // If this task isn't running, then use its start time
                        // as a potential next event start time.
                        if(this_start < candidate_next_time) {
                            candidate_next_time = this_start;
                        } 
                    } else if(!forward && this_start < candidate_time) {
                        if(this_start > candidate_next_time) {
                            candidate_next_time = this_start;    
                        }
                    }
                    
                    if(forward && this_end > candidate_time) {
                        // Also try its end time
                        if(this_end < candidate_next_time) {
                            candidate_next_time = this_end;
                        }
                    } else if(!forward && this_end < candidate_time) {
                        if(this_end > candidate_next_time) {
                            candidate_next_time = this_end;    
                        }
                    }
                    

                    // Get the start time of the next event
                    // or end time of the prev event
                    TraceData::event_list_t::const_iterator next = 
                        forward ? trace_data->get_next_compute_event(loc, task->second) : 
                          trace_data->get_prev_compute_event(loc, task->first);
                    const uint64_t next_time = next->get_time();
                    if((forward && next_time < candidate_next_time) || (!forward && next_time > candidate_next_time)) {
                        candidate_next_time = next_time;
                    }
                } else {
                    std::cerr << "ERROR: No task found for candidate time." << std::endl;
                    throw std::runtime_error("Task not found in region.");
                }
            }
            if(tasks_running == 1) {
                end_event = candidate_event;
            }
            if((forward && candidate_next_time == std::numeric_limits<uint64_t>::max()) || (!forward && candidate_next_time == std::numeric_limits<uint64_t>::min())) {
                std::cerr << "ERROR: candidate_next_time should have changed." << std::endl;
                throw std::runtime_error("No next event found");
            }
            if(candidate_next_time == candidate_time) {
                std::cerr << "ERROR: candidate_time should have changed." << std::endl;
                throw std::runtime_error("Iteration repeated");
            }
            if(forward && candidate_next_time < candidate_time) {
                std::cerr << "ERROR: candidate_time should not have decreased in forward mode." << std::endl;
                throw std::runtime_error("Bad candidate time");
            }
            if(!forward && candidate_next_time > candidate_time) {
                std::cerr << "ERROR: candidate_time should not have increased in backward mode." << std::endl;
                throw std::runtime_error("Bad candidate time");
            }
            if(!forward && candidate_next_time == 0) {
                std::cerr << "ERROR: should not have reached beginning of trace." << std::endl;
                throw std::runtime_error("Bad candidate time");
            }
            candidate_time = forward ? candidate_next_time + 1 : candidate_next_time - 1;
        }
        if(end_event == nullptr) {
            std::cerr << "ERROR: end_event should not be null." << std::endl;
            throw std::runtime_error("No region-breaking task found");
        } else {
            if(forward && end_event->get_time() > last_time) {
                std::cerr << "ERROR: End event should not occur after next full occupancy!" << std::endl;
                throw std::runtime_error("Region-breaking task outside region.");
            } else if(!forward && end_event->get_time() < first_time) {
                std::cerr << "ERROR: End event should not occur before previous full occupancy!" << std::endl;
                throw std::runtime_error("Region-breaking task outside region.");
            }
            list.push_back(end_event);
        }
        ++region_num;
    }
}

void IdleDetector::find_connection_between(const TraceData::Event * start_event,
        const TraceData::Event * end_event) {
    if(start_event == nullptr) {
        std::cerr << "ERROR: start_event is null" << std::endl;
        throw std::invalid_argument("start_event");
    }
    if(end_event == nullptr) {
        std::cerr << "ERROR: end_event is null" << std::endl;
        throw std::invalid_argument("end_event");
    }
    // Work backwards from end to start to find connection
    const uint64_t start_event_time = start_event->get_time();
    const TraceData::Event * current_event = end_event;
    connections.emplace_back();
    auto & path = connections.back();
    path.emplace_back(end_event);
    while(current_event != nullptr && current_event != start_event && current_event->get_time() > start_event_time) {
        // When did the current event become runnable?
        const std::string & guid = current_event->get_object().get_guid();
        const auto & events = trace_data->get_events_for_guid(guid);
        uint64_t runnable_time = TraceData::INVALID_TIME;
        OTF2_LocationRef runnable_loc = TraceData::INVALID_LOCATION_REF;
        for(const auto & event : events) {
            if(event->get_event_type() == TraceData::EventType::TaskRunnable) {
                // Check to make sure I'm the object rather than the parent
                if(event->get_object().get_guid() == guid) {
                    runnable_time = event->get_time();
                    runnable_loc = event->get_loc();
                    break;
                }
            }
        }
        if(runnable_time == TraceData::INVALID_TIME || runnable_loc == TraceData::INVALID_LOCATION_REF) {
            std::cerr << "ERROR: Task " << guid << " has no associated TaskRunnable trace event" << std::endl;
            throw std::runtime_error("Bad trace");
        } else {
            auto task_when_became_runnable = trace_data->get_task_iter_at_time(runnable_loc, runnable_time, true);
            if(task_when_became_runnable) {
                const TraceData::Event * next_event = &(*(task_when_became_runnable->first));
                if(next_event == current_event) {
                    std::cerr << "ERROR: next_event should not be identical to current_event" << std::endl;
                    throw std::runtime_error("Iteration repeated");
                }
                current_event = next_event;
                path.emplace_back(current_event);
            } else {
                throw std::runtime_error("Bad trace");
            }
        }

    }
}

void IdleDetector::find_connections() {
    uint64_t region_num = 0;
    for(auto region : idle_regions) {
        ATV_UNUSED(region);
        const TraceData::Event * start_event = region_start_events[region_num];
        const TraceData::Event * end_event   = region_end_events[region_num];
        find_connection_between(start_event, end_event);
        ++region_num;
    }
}

void IdleDetector::analyze() {
    if(trace_data == nullptr) {
        return;
    }

    calculate_occupancy();
    find_idle_regions();
    find_region_boundary_events(true,  false, true,  occupancy_threshold, region_start_events);
    find_region_boundary_events(true,  true,  false, occupancy_threshold, region_end_events);
    find_connections();
}

std::string IdleDetector::get_report() const {
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

    ss << std::setw(6) << std::right << "Region" << " ";
    ss << std::setw(11) << std::right << "Start" << " ";
    ss << std::setw(11) << std::right << "End" << " ";
    ss << std::setw(11) << std::right << "Length" << " ";
    //ss << std::setw(10) << "Next" << " ";
    //ss << std::setw(10) << std::right << "Start Occ" << " ";
    //ss << std::setw(10) << std::right << "End Occ" << " ";
    ss << std::setw(16) << std::left << "Initiating Task" << " ";
    ss << std::setw(16) << std::left << "GUID" << " ";
    ss << std::setw(16) << std::left << "Breaking Task" << " ";
    ss << std::setw(16) << std::left << "GUID" << "\n";
    uint64_t region_num = 0;
    for(auto region : idle_regions) {
        const double start =  (std::get<0>(region) * interval_sec);
        const double end =  (std::get<1>(region) * interval_sec);
        const double len = end - start;
        //const double next = (std::get<2>(region) * interval_sec);
        const std::string init_name = region_start_events[region_num]->get_object().get_name();
        const std::string init_guid = region_start_events[region_num]->get_object().get_guid();
        const std::string break_name = region_end_events[region_num]->get_object().get_name();
        const std::string break_guid = region_end_events[region_num]->get_object().get_guid();
        ss << std::setw(6) << std::right << region_num << " ";
        ss << std::setw(11) << std::right << std::fixed << std::setprecision(3) << start << " ";
        ss << std::setw(11) << std::right << std::fixed << std::setprecision(3) << end << " ";
        ss << std::setw(11) << std::right << std::fixed << std::setprecision(3) << len << " ";
        //ss << std::setw(10) << std::fixed << std::setprecision(3) << next << " ";
        //ss << std::setw(10) << std::right << std::get<3>(region) << " ";
        //ss << std::setw(10) << std::right << std::get<4>(region) << " ";
        ss << std::setw(16) << std::left << init_name << " ";
        ss << std::setw(16) << std::left << init_guid << " ";
        ss << std::setw(16) << std::left << break_name << " ";
        ss << std::setw(16) << std::left << break_guid << "\n";
        ++region_num;
    }

    ss << "\n";
    ss << std::setw(10) << "Starved:" << " ";
    ss << std::setw(10) << starved_time << " ";

    ss << std::endl << std::endl;

    region_num = 0;
    for(auto region : idle_regions) {
        ATV_UNUSED(region);
        ss << std::setw(6) << std::right << region_num << " ";
        const auto & path = connections[region_num];
        bool first_event = true;
        for(const auto event : path) {
            if(!first_event) {
                ss << std::setw(6) << std::right << " " << " ";
            }        
            first_event = false;
            const auto & obj = event->get_object();
            ss << std::setw(30) << std::left << obj.get_name() << " ";
            ss << std::setw(20) << std::left << obj.get_guid() << std::endl;
        }
        ++region_num;
        ss << std::endl;
    }

    return ss.str();
}

void IdleDetector::set_trace_data(TraceData * trace_data) {
   this->trace_data = trace_data;
   setup();
}

