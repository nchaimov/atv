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
#include <stdexcept>
#include <functional>

#include <otf2/otf2.h>

#include "status.hpp"
#include "callbacks.hpp"
#include "trace_reader.hpp"

TraceReader::TraceReader(std::string & filename, const TraceReader::locations_t & locations, Callbacks * callbacks) : anchor(filename), locations(locations), callbacks(callbacks) {
    
    reader = OTF2_Reader_Open(filename.c_str());
    if(reader == nullptr) {
        std::cerr << "Unable to open OTF2 anchor file at " << filename << std::endl;
        throw std::runtime_error("Unable to open OTF2 anchor file.");
    }

    try {
        OTF2_ErrorCode status;
        
        status = OTF2_Reader_SetSerialCollectiveCallbacks(reader);
        check_status(status, "OTF2_Reader_SetSerialCollectiveCallbacks");

    } catch(std::exception & e) {
        std::cerr << "Unable to setup OTF2 reader: " << e.what() << std::endl;
        throw e;
    }

}

TraceReader::~TraceReader() {
    if(reader != nullptr) {
        OTF2_Reader_Close(reader);
    }
}

ATVStatus TraceReader::read_traces(std::function<void(uint64_t)> progress_callback) {
    if(reader == nullptr) {
        return ATVStatus::ERROR;
    }

    try {
        OTF2_ErrorCode status;
        
        uint64_t num_global_locations;
        status = OTF2_Reader_GetNumberOfLocations(reader, &num_global_locations);
        check_status(status, "OTF2_Reader_GetNumberOfLocations");
        std::cerr << "num global locations: " << num_global_locations << std::endl;

        void * user_data = callbacks->get_user_data();

        // Set global definition callbacks
        OTF2_GlobalDefReader * global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
        check_ptr(global_def_reader, "OTF2_Reader_GetGlobalDefReader");
        OTF2_GlobalDefReaderCallbacks * global_def_callbacks = callbacks->get_global_def_callbacks();
        check_ptr(global_def_callbacks, "callbacks->get_global_def_callbacks");
        if(global_def_callbacks != nullptr) {
            status = OTF2_Reader_RegisterGlobalDefCallbacks(reader, global_def_reader, global_def_callbacks, user_data);
        }
        check_status(status, "OTF2_Reader_RegisterGlobalDefCallbacks");

        // Read global definitions
        uint64_t definitions_read;
        status = OTF2_Reader_ReadAllGlobalDefinitions(reader, global_def_reader, &definitions_read);
        check_status(status, "OTF2_Reader_ReadAllGlobalDefinitions");
        std::cerr << "global defs read: " << definitions_read << std::endl;

        // Cleanup
        status = OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader);
        check_status(status, "OTF2_Reader_CloseGlobalDefReader");

        if(num_global_locations > 0) {
            // Set global event callbacks
            OTF2_GlobalEvtReader * global_evt_reader = OTF2_Reader_GetGlobalEvtReader(reader);
            check_ptr(global_evt_reader, "OTF2_Reader_GetGlobalEvtReader");
            OTF2_GlobalEvtReaderCallbacks * global_evt_callbacks = callbacks->get_global_evt_callbacks();
            check_ptr(global_evt_callbacks, "callbacks->get_global_evt_callbacks");
            if(global_evt_callbacks != nullptr) {
                status = OTF2_Reader_RegisterGlobalEvtCallbacks(reader, global_evt_reader, global_evt_callbacks, user_data);
                check_status(status, "OTF2_Reader_RegisterGlobalEvtCallbacks");
            }

            // Read global events
            uint64_t events_read;
            status = OTF2_Reader_ReadAllGlobalEvents(reader, global_evt_reader, &events_read);
            check_status(status, "OTF2_Reader_ReadAllGlobalEvents");
            std::cerr << "global evts read: " << events_read << std::endl;

            // Cleanup
            status = OTF2_Reader_CloseGlobalEvtReader(reader, global_evt_reader);
            check_status(status, "OTF2_Reader_CloseGlobalEvtReader");
        }

        uint64_t locs_processed = 0;
        for(uint64_t loc : locations) {
            callbacks->set_current_location(loc);
            // Set local definition callbacks
            status = OTF2_Reader_SelectLocation(reader, loc);
            check_status(status, "OTF2_Reader_SelectLocation");
            status = OTF2_Reader_OpenDefFiles(reader);
            check_status(status, "OTF2_Reader_OpenDefFiles");
            OTF2_DefReader* def_reader = OTF2_Reader_GetDefReader(reader, loc);
            check_ptr(def_reader, "OTF2_Reader_GetDefReader");
            OTF2_DefReaderCallbacks * def_callbacks = callbacks->get_def_callbacks();
            check_ptr(def_callbacks, "callbacks->get_def_callbacks");
            if(def_callbacks != nullptr) {
                status = OTF2_Reader_RegisterDefCallbacks(reader, def_reader, def_callbacks, user_data);
                check_status(status, "OTF2_Reader_RegisterDefCallbacks");
            }

            // Read local definitions
            uint64_t local_defs_read;
            status = OTF2_Reader_ReadAllLocalDefinitions(reader, def_reader, &local_defs_read);
            check_status(status, "OTF2_Reader_ReadAllLocalDefinitions");
            std::cerr << "loc: " << loc << ", local defs read: " << local_defs_read << std::endl;
            status = OTF2_Reader_CloseDefReader(reader, def_reader);
            check_status(status, "OTF2_Reader_CloseDefReader");

            // Set local event callbacks
            status = OTF2_Reader_SelectLocation(reader, loc);
            check_status(status, "OTF2_Reader_SelectLocation");
            status = OTF2_Reader_OpenEvtFiles(reader);
            check_status(status, "OTF2_Reader_OpenEvtFiles");
            OTF2_EvtReader* evt_reader = OTF2_Reader_GetEvtReader(reader, loc);
            check_ptr(evt_reader, "OTF2_Reader_GetEvtReader");
            OTF2_EvtReaderCallbacks * evt_callbacks = callbacks->get_evt_callbacks();
            check_ptr(evt_callbacks, "callbacks->get_evt_callbacks");
            if(evt_callbacks != nullptr) {
                status = OTF2_Reader_RegisterEvtCallbacks(reader, evt_reader, evt_callbacks, user_data);
                check_status(status, "OTF2_Reader_RegisterEvtCallbacks");
            }

            // Read local events
            uint64_t local_evts_read;
            status = OTF2_Reader_ReadAllLocalEvents(reader, evt_reader, &local_evts_read);
            check_status(status, "OTF2_Reader_ReadAllLocalEvents");
            std::cerr << "loc: " << loc << ", local evts read: " << local_evts_read << std::endl;
            status = OTF2_Reader_CloseEvtReader(reader, evt_reader);
            check_status(status, "OTF2_Reader_CloseEvtReader");

            locs_processed++;
            if(progress_callback) {
                progress_callback(locs_processed);
            }
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

