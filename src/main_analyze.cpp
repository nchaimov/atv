#include <iostream>

#include "files.hpp"
#include "idle_detector.hpp"
#include "trace_data.hpp"

int main(int argc, char * argv[]) {
    std::string filename = process_command_line(argc, argv);
    const TraceReader::locations_t locations = get_locations(filename);
    DefaultCallbacks callbacks;
    TraceReader reader{filename, locations, &callbacks};
    reader.read_traces();      
    TraceData * trace_data = callbacks.get_trace_data();
    IdleDetector idle_detector(trace_data, 0.001, 3, 2);
    idle_detector.analyze();
    std::cerr << idle_detector.get_report() << std::endl;
    return 0;
}
