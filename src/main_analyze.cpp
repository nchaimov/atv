#include <iostream>

#include "files.hpp"
#include "idle_detector.hpp"
#include "trace_data.hpp"

int main(int argc, char * argv[]) {
    std::string filename = process_command_line(argc, argv);
    const TraceReader::locations_t locations = get_locations(filename);
    DefaultCallbacks callbacks;
    TraceData * trace_data = callbacks.get_trace_data();
    trace_data->set_selective_guid_map_events({TraceData::EventType::TaskRunnable});
    TraceReader reader{filename, locations, &callbacks};
    reader.read_traces();      
    IdleDetector idle_detector(trace_data, 0.0001, 50, 2);
    idle_detector.analyze();
    std::cout << idle_detector.get_report() << std::endl;
    return 0;
}
