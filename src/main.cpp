
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>

#include <boost/program_options.hpp> 
#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp> 
#include <boost/range/iterator_range.hpp>
#include <boost/lexical_cast.hpp>

#include "status.hpp"
#include "trace_reader.hpp"
#include "callbacks.hpp"

std::string process_command_line(int argc, char * argv[]) {
    std::string filename;
    try {
        namespace po = boost::program_options; 
        po::options_description desc("Options"); 
        desc.add_options()
            ("help,h", "print usage message")
            ("filename", po::value<std::string>(&filename)->required(), "path to trace anchor file");
        po::positional_options_description pos_opts;
        pos_opts.add("filename", 1);
        po::variables_map vm;
        try {
            po::store(po::command_line_parser(argc, argv).options(desc).positional(pos_opts).run(), vm);  
            po::notify(vm);

            if (vm.count("help")) {  
                std::cout << desc << std::endl;
                std::exit(0);
            }

        } catch(boost::program_options::required_option & e) {
            std::cerr << "command line error: " << e.what() << std::endl;    
            std::cerr << desc << std::endl;
            std::exit(1);
        }
    } catch(std::exception & e) {
        std::cerr << e.what() << std::endl;
        std::exit(1);
    }
    return filename;
}

TraceReader::locations_t get_locations(std::string anchor) {
    namespace fs = ::boost::filesystem;
    const fs::path p(anchor);
    if(!fs::exists(p)) {
        throw std::runtime_error("Anchor file does not exist: " + p.string());
    }
    if(!fs::is_regular_file(p)) {
        throw std::runtime_error("Anchor file is not a regular file: " + p.string());
    }
    const fs::path parent = p.parent_path();
    const fs::path stem = p.stem();
    fs::path local_dir = parent;
    local_dir /= stem;
    if(!fs::exists(local_dir)) {
        throw std::runtime_error("Local files directory does not exist: " + local_dir.string());
    }
    if(!fs::is_directory(local_dir)) {
        throw std::runtime_error("Local files path is not a directory: " + local_dir.string());
    }
    TraceReader::locations_t locations;
    for(auto & entry : boost::make_iterator_range(fs::directory_iterator(local_dir), {})) {
        const fs::path e = entry.path();
        const std::string ext = e.extension().string();
        if(ext == ".def") {
            const uint64_t loc = boost::lexical_cast<uint64_t>(e.stem().string());
            locations.push_back(loc);
        }
    }
    
    return locations;

}

int main(int argc, char * argv[]) {

    std::string filename = process_command_line(argc, argv);
    const TraceReader::locations_t locations = get_locations(filename);

    DefaultCallbacks callbacks;
    TraceReader reader{filename, locations, &callbacks};
    ATVStatus status = reader.read_traces();

    TraceData * trace_data = callbacks.get_trace_data();
    for(const auto & loc_p : trace_data->get_locations()) {
       const auto & loc = loc_p.second;
       std::cerr << "Location: " << loc.get_loc() << " " << loc.get_name() << " in location group " << loc.get_parent().get_self() << " " << loc.get_parent().get_name() << " in system tree node " << loc.get_parent().get_parent().get_self() << " " << loc.get_parent().get_parent().get_name() << std::endl;
    }

    if(status == ATVStatus::OK) {
        return 0;               
    } else {
        return 1;
    }

}
