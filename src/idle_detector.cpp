#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

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
            candidate_regions.push_back(std::make_tuple(candidate_start, candidate_end, occupancy[candidate_start], occupancy[candidate_end]));
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

    ss << std::setw(10) << "Region" << " ";
    ss << std::setw(10) << "Start" << " ";
    ss << std::setw(10) << "End" << " ";
    ss << std::setw(10) << "Length" << " ";
    ss << std::setw(10) << "Start Occ" << " ";
    ss << std::setw(10) << "End Occ" << "\n";
    uint64_t region_num = 0;
    for(auto region : idle_regions) {
        const double start =  (std::get<0>(region) * interval_sec);
        const double end =  (std::get<1>(region) * interval_sec);
        const double len = end - start;
        ss << std::setw(10) << region_num << " ";
        ss << std::setw(10) << std::fixed << std::setprecision(3) << start << " ";
        ss << std::setw(10) << std::fixed << std::setprecision(3) << end << " ";
        ss << std::setw(10) << std::fixed << std::setprecision(3) << len << " ";
        ss << std::setw(10) << std::get<2>(region) << " ";
        ss << std::setw(10) << std::get<3>(region) << "\n";
        ++region_num;
    }

    ss << std::setw(10) << "Starved:" << " ";
    ss << std::setw(10) << starved_time << " ";

    ss << std::endl;

    return ss.str();
}

void IdleDetector::set_trace_data(TraceData * trace_data) {
   this->trace_data = trace_data;
   setup();
}

