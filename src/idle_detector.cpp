#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "idle_detector.hpp"
#include "trace_data.hpp"
#include <otf2/otf2.h>
 


IdleDetector::IdleDetector(TraceData * trace_data, double interval_sec, uint64_t length_threshold, uint64_t decrease_threshold)
        : trace_data(trace_data), interval_sec(interval_sec), length_threshold(length_threshold), decrease_threshold(decrease_threshold)  {
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

    // Now scan for decreasing segments
    uint64_t segment_start = 0;
    uint64_t segment_end = 0;
    double last_occupancy = max_occupancy;
    bool in_decreasing_segment = false;
    idle_region_list_t candidate_regions;
    for(uint64_t sample = 1; sample < num_samples; ++sample) {
        uint64_t & s = occupancy[sample];
        if(in_decreasing_segment && (s > last_occupancy || s == max_occupancy) ) {
            // End a segment
            segment_end = sample-1;  
            in_decreasing_segment = false;
            // No 0-length segments
            if(segment_start != segment_end && occupancy[segment_start] - occupancy[segment_end] > decrease_threshold) {
                candidate_regions.push_back(std::make_tuple(segment_start, segment_end, occupancy[segment_start], occupancy[segment_end]));
            }
        } else if (!in_decreasing_segment && (s < last_occupancy)) {
            // Start a segment
            segment_start = sample-1;
            in_decreasing_segment = true;
        } 
        last_occupancy = s;
    }

    // Join nearly-adjacent regions
    const uint64_t num_candidates = candidate_regions.size();
    segment_start = 0;
    segment_end = 0;
    idle_region_list_t joined_regions;
    for(uint64_t candidate = 0; candidate < num_candidates; ++candidate) {
        if(segment_start == 0) {
            segment_start = std::get<0>(candidate_regions[candidate]);
            segment_end = std::get<1>(candidate_regions[candidate]);
        } else {
            const uint64_t this_start = std::get<0>(candidate_regions[candidate]);
            if(this_start - segment_end < length_threshold) {
                // Join
                segment_end = std::get<1>(candidate_regions[candidate]);
            } else {
                // End of joined region
                if(segment_end - segment_start > length_threshold) {
                    joined_regions.push_back(std::make_tuple(segment_start, segment_end, occupancy[segment_start], occupancy[segment_end]));
                }
                segment_start = 0;
                segment_end = 0;
            }
        }    
    }

    idle_regions = joined_regions;

}

std::string IdleDetector::get_report() {
    std::stringstream ss;
    
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
    

    ss << std::setw(10) << "Region" << " ";
    ss << std::setw(10) << "Start" << " ";
    ss << std::setw(10) << "End" << " ";
    ss << std::setw(10) << "Start Occ" << " ";
    ss << std::setw(10) << "End Occ" << "\n";
    uint64_t region_num = 0;
    for(auto region : idle_regions) {
        ss << std::setw(10) << region_num << " ";
        ss << std::setw(10) << std::get<0>(region) << " ";
        ss << std::setw(10) << std::get<1>(region) << " ";
        ss << std::setw(10) << std::get<2>(region) << " ";
        ss << std::setw(10) << std::get<3>(region) << "\n";
        ++region_num;
    }

    return ss.str();
}

void IdleDetector::set_trace_data(TraceData * trace_data) {
   this->trace_data = trace_data;
   setup();
}

