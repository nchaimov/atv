#include <iostream>

#include "files.hpp"
#include "trace_data.hpp"

int main(int argc, char * argv[]) {
    std::string filename = process_command_line(argc, argv);
    const TraceReader::locations_t locations = get_locations(filename);
    DefaultCallbacks callbacks;
    TraceData * trace_data = callbacks.get_trace_data();
    trace_data->set_ignore_event_names({"processRequestEdt"});
    TraceReader reader{filename, locations, &callbacks};
    reader.read_traces();      
    std::cout << "Global offset:\t" << trace_data->get_global_offset() << std::endl;
    std::cout << "Trace length:\t"  << trace_data->get_trace_length() << std::endl;
    std::cout << "End time:\t" << trace_data->get_global_offset() + trace_data->get_trace_length() << std::endl;
    std::cout << "Resolution:\t" << trace_data->get_timer_resolution() << std::endl;
    for(OTF2_LocationRef loc_ref : trace_data->get_location_refs()) {
        for(const auto & event : trace_data->get_events(loc_ref)) {
            std::cout << event.to_string() << std::endl;
        }
    }
    return 0;
}
