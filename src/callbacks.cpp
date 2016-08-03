#include "callbacks.hpp"
#include <otf2/otf2.h>

OTF2_GlobalDefReaderCallbacks * DefaultCallbacks::get_global_def_callbacks() const {
    return global_def_callbacks;
}

OTF2_GlobalEvtReaderCallbacks * DefaultCallbacks::get_global_evt_callbacks() const {
    return global_evt_callbacks;
}

OTF2_DefReaderCallbacks * DefaultCallbacks::get_def_callbacks() const {
    return def_callbacks;
}

OTF2_EvtReaderCallbacks * DefaultCallbacks::get_evt_callbacks() const {
    return evt_callbacks;
}

void DefaultCallbacks::set_current_location(const OTF2_LocationRef loc) {
    trace_data->set_current_location(loc);
}

void * DefaultCallbacks::get_user_data() const {
    return static_cast<void *>(trace_data);
}

TraceData * DefaultCallbacks::get_trace_data() const {
    return trace_data;
}

DefaultCallbacks::DefaultCallbacks() {
    global_def_callbacks = ATV_CreateGlobalDefReaderCallbacks();
    global_evt_callbacks = ATV_CreateGlobalEvtReaderCallbacks();
    def_callbacks = ATV_CreateDefReaderCallbacks();
    evt_callbacks = ATV_CreateEvtReaderCallbacks();
    trace_data = new TraceData();
}

DefaultCallbacks::~DefaultCallbacks() {
    OTF2_GlobalDefReaderCallbacks_Delete(global_def_callbacks);
    OTF2_GlobalEvtReaderCallbacks_Delete(global_evt_callbacks);
    OTF2_DefReaderCallbacks_Delete(def_callbacks);
    OTF2_EvtReaderCallbacks_Delete(evt_callbacks);
    delete trace_data;
}
