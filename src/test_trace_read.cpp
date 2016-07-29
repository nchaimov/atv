/* Copyright (c) 2016 University of Oregon
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

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


#include <otf2/otf2.h>

#include "status.h"
#include "callbacks.h"

inline static void check_status(const OTF2_ErrorCode status, const std::string & msg) {
    const char * errname = OTF2_Error_GetName(status);
    const char * errdesc = OTF2_Error_GetDescription(status);
    if(status != OTF2_SUCCESS) {
        throw std::runtime_error(msg + ": " + errname + ": " + errdesc);
    }
}       

template<typename T>
inline static void check_ptr(const T* ptr, const std::string & msg) {
    if(ptr == nullptr) {
        throw std::runtime_error(msg + ": Null pointer");    
    }
}


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

ATVStatus setup_reader(OTF2_Reader *& reader, std::string & filename) {
    
    reader = OTF2_Reader_Open(filename.c_str());
    if(reader == nullptr) {
        std::cerr << "Unable to open OTF2 anchor file at " << filename << std::endl;
        return ATVStatus::ERROR;
    }

    try {
    OTF2_ErrorCode status;
    
    status = OTF2_Reader_SetSerialCollectiveCallbacks(reader);
    check_status(status, "OTF2_Reader_SetSerialCollectiveCallbacks");

    } catch(std::exception & e) {
        std::cerr << e.what() << std::endl;
        return ATVStatus::ERROR;
    }

    return ATVStatus::OK;
}

ATVStatus read_traces(OTF2_Reader * reader, const std::vector<uint64_t> & locations) {
    if(reader == nullptr) {
        return ATVStatus::ERROR;
    }

    try {
        OTF2_ErrorCode status;
        
        uint64_t num_global_locations;
        status = OTF2_Reader_GetNumberOfLocations(reader, &num_global_locations);
        check_status(status, "OTF2_Reader_GetNumberOfLocations");
        std::cout << "num global locations: " << num_global_locations << std::endl;

        // Set global definition callbacks
        OTF2_GlobalDefReader * global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
        check_ptr(global_def_reader, "OTF2_Reader_GetGlobalDefReader");
        OTF2_GlobalDefReaderCallbacks * global_def_callbacks = ATV_CreateGlobalDefReaderCallbacks();
        check_ptr(global_def_callbacks, "ATV_CreateGlobalDefReaderCallbacks");
        status = OTF2_Reader_RegisterGlobalDefCallbacks(reader, global_def_reader, global_def_callbacks, nullptr);
        check_status(status, "OTF2_Reader_RegisterGlobalDefCallbacks");
        OTF2_GlobalDefReaderCallbacks_Delete(global_def_callbacks);

        // Read global definitions
        uint64_t definitions_read;
        status = OTF2_Reader_ReadAllGlobalDefinitions(reader, global_def_reader, &definitions_read);
        check_status(status, "OTF2_Reader_ReadAllGlobalDefinitions");
        std::cout << "global defs read: " << definitions_read << std::endl;

        // Cleanup
        status = OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader);
        check_status(status, "OTF2_Reader_CloseGlobalDefReader");

        if(num_global_locations > 0) {
            // Set global event callbacks
            OTF2_GlobalEvtReader * global_evt_reader = OTF2_Reader_GetGlobalEvtReader(reader);
            check_ptr(global_evt_reader, "OTF2_Reader_GetGlobalEvtReader");
            OTF2_GlobalEvtReaderCallbacks * global_evt_callbacks = ATV_CreateGlobalEvtReaderCallbacks();
            check_ptr(global_evt_callbacks, "ATV_CreateGlobalEvtReaderCallbacks");
            status = OTF2_Reader_RegisterGlobalEvtCallbacks(reader, global_evt_reader, global_evt_callbacks, nullptr);
            check_status(status, "OTF2_Reader_RegisterGlobalEvtCallbacks");
            OTF2_GlobalEvtReaderCallbacks_Delete(global_evt_callbacks);

            // Read global events
            uint64_t events_read;
            status = OTF2_Reader_ReadAllGlobalEvents(reader, global_evt_reader, &events_read);
            check_status(status, "OTF2_Reader_ReadAllGlobalEvents");
            std::cout << "global evts read: " << events_read << std::endl;

            // Cleanup
            status = OTF2_Reader_CloseGlobalEvtReader(reader, global_evt_reader);
            check_status(status, "OTF2_Reader_CloseGlobalEvtReader");
        }

        for(uint64_t loc : locations) {
            // Set local definition callbacks
            status = OTF2_Reader_SelectLocation(reader, loc);
            check_status(status, "OTF2_Reader_SelectLocation");
            status = OTF2_Reader_OpenDefFiles(reader);
            check_status(status, "OTF2_Reader_OpenDefFiles");
            OTF2_DefReader* def_reader = OTF2_Reader_GetDefReader(reader, loc);
            check_ptr(def_reader, "OTF2_Reader_GetDefReader");
            OTF2_DefReaderCallbacks * def_callbacks = ATV_CreateDefReaderCallbacks();
            check_ptr(def_callbacks, "ATV_CreateDefReaderCallbacks");
            status = OTF2_Reader_RegisterDefCallbacks(reader, def_reader, def_callbacks, nullptr);
            check_status(status, "OTF2_Reader_RegisterDefCallbacks");
            OTF2_DefReaderCallbacks_Delete(def_callbacks);

            // Read local definitions
            uint64_t local_defs_read;
            status = OTF2_Reader_ReadAllLocalDefinitions(reader, def_reader, &local_defs_read);
            check_status(status, "OTF2_Reader_ReadAllLocalDefinitions");
            std::cout << "loc: " << loc << ", local defs read: " << local_defs_read << std::endl;
            status = OTF2_Reader_CloseDefReader(reader, def_reader);
            check_status(status, "OTF2_Reader_CloseDefReader");

            // Set local event callbacks
            status = OTF2_Reader_SelectLocation(reader, loc);
            check_status(status, "OTF2_Reader_SelectLocation");
            status = OTF2_Reader_OpenEvtFiles(reader);
            check_status(status, "OTF2_Reader_OpenEvtFiles");
            OTF2_EvtReader* evt_reader = OTF2_Reader_GetEvtReader(reader, loc);
            check_ptr(evt_reader, "OTF2_Reader_GetEvtReader");
            OTF2_EvtReaderCallbacks * evt_callbacks = ATV_CreateEvtReaderCallbacks();
            check_ptr(evt_callbacks, "ATV_CreateEvtReaderCallbacks");
            status = OTF2_Reader_RegisterEvtCallbacks(reader, evt_reader, evt_callbacks, nullptr);
            check_status(status, "OTF2_Reader_RegisterEvtCallbacks");
            OTF2_EvtReaderCallbacks_Delete(evt_callbacks);

            // Read local events
            uint64_t local_evts_read;
            status = OTF2_Reader_ReadAllLocalEvents(reader, evt_reader, &local_evts_read);
            check_status(status, "OTF2_Reader_ReadAllLocalEvents");
            std::cout << "loc: " << loc << ", local evts read: " << local_evts_read << std::endl;
            status = OTF2_Reader_CloseEvtReader(reader, evt_reader);
            check_status(status, "OTF2_Reader_CloseEvtReader");

        }

        // Cleanup
        status = OTF2_Reader_CloseDefFiles(reader);
        check_status(status, "OTF2_Reader_CloseDefFiles");
        

    }  catch(std::exception & e) {
        std::cerr << e.what() << std::endl;
        return ATVStatus::ERROR;
    }  

    return ATVStatus::OK;
}

std::vector<uint64_t> get_locations(std::string anchor) {
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
    std::vector<uint64_t> locations;
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
    std::vector<uint64_t> locations = get_locations(filename);

    OTF2_Reader * reader;
    ATVStatus status = setup_reader(reader, filename);
    if(status == ATVStatus::ERROR) {
        return 1;
    }
    status = read_traces(reader, locations);
    
    OTF2_ErrorCode err = OTF2_Reader_Close(reader);
    check_status(err, "OTF2_Reader_Close");


    return 0;
}

