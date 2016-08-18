#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include "trace_reader.hpp"

std::string process_command_line(int argc, char * argv[]);
TraceReader::locations_t get_locations(std::string anchor);

#endif
