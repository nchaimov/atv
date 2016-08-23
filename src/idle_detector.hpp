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

    using occupancy_list_t = std::vector<uint64_t>;
    occupancy_list_t occupancy;
    using region_t = std::tuple<uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t>;
    using idle_region_list_t = std::vector<region_t>;
    idle_region_list_t idle_regions;
    uint32_t max_occupancy = 0;
    double starved_time = 0.0;
    using event_list_t = std::vector<const TraceData::Event*>;
    event_list_t region_start_events;
    event_list_t region_end_events;
    using events_list_t = std::vector<event_list_t>;
    events_list_t connections;

    void setup();
    void calculate_occupancy();
    void find_idle_regions();
    void find_region_boundary_events(const bool forward, const bool decreasing, const bool from_start, const uint64_t threshold, event_list_t & list);
    void find_connection_between(const TraceData::Event * start_event, const TraceData::Event * end_event);
    void find_connections();

public:
    IdleDetector(TraceData * trace_data, double interval_sec, uint64_t length_threshold, uint64_t occupancy_threshold);
    virtual ~IdleDetector();

    void set_trace_data(TraceData * trace_data);
    void analyze();
    std::string get_report() const;

    const occupancy_list_t & get_occupancy() const { return occupancy; } ;
    const idle_region_list_t  & get_idle_regions() const { return idle_regions; } ;
    const event_list_t & get_region_start_events() const { return region_start_events; } ;
    const event_list_t & get_region_end_events() const { return region_end_events; } ;

};


#endif
