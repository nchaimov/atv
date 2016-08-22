#ifndef IDLE_DETECTOR_HPP
#define IDLE_DETECTOR_HPP

#include "trace_data.hpp"
#include <vector>
#include <stdint.h>
#include <tuple>

class IdleDetector {

protected:
    TraceData * trace_data;
    double interval_sec;
    uint64_t length_threshold;
    uint64_t occupancy_threshold;

    double interval;
    double start;
    double end;
    uint64_t num_samples;

    std::vector<uint64_t> occupancy;
    using region_t = std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t>;
    using idle_region_list_t = std::vector<region_t>;
    idle_region_list_t idle_regions;
    uint32_t max_occupancy = 0;
    double starved_time = 0.0;
    std::vector<const TraceData::Event*> region_end_events;

    void setup();
    void calculate_occupancy();
    void find_idle_regions();
    void find_region_end_events();

public:
    IdleDetector(TraceData * trace_data, double interval_sec, uint64_t length_threshold, uint64_t occupancy_threshold);
    virtual ~IdleDetector();

    void set_trace_data(TraceData * trace_data);
    void analyze();
    std::string get_report();

};


#endif
