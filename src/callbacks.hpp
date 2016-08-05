#ifndef ATV_CALLBACKS_H
#define ATV_CALLBACKS_H

#include <otf2/otf2.h>
#include "ATV_DefReaderCallbacks.h"
#include "ATV_EvtReaderCallbacks.h"
#include "ATV_GlobalDefReaderCallbacks.h"
#include "ATV_GlobalEvtReaderCallbacks.h"
#include "trace_data.hpp"

class Callbacks {
public:
    virtual OTF2_GlobalDefReaderCallbacks * get_global_def_callbacks() const =0;
    virtual OTF2_GlobalEvtReaderCallbacks * get_global_evt_callbacks() const =0;
    virtual OTF2_DefReaderCallbacks * get_def_callbacks() const = 0;
    virtual OTF2_EvtReaderCallbacks * get_evt_callbacks() const = 0;
    virtual void set_current_location(const OTF2_LocationRef ref) = 0;
    virtual void * get_user_data() const = 0;
    Callbacks() {};
    virtual ~Callbacks() {};
};

class DefaultCallbacks : public Callbacks {
private:
    OTF2_GlobalDefReaderCallbacks * global_def_callbacks;
    OTF2_GlobalEvtReaderCallbacks * global_evt_callbacks;
    OTF2_DefReaderCallbacks * def_callbacks;
    OTF2_EvtReaderCallbacks * evt_callbacks;
    TraceData * trace_data;
public:
    virtual OTF2_GlobalDefReaderCallbacks * get_global_def_callbacks() const override;
    virtual OTF2_GlobalEvtReaderCallbacks * get_global_evt_callbacks() const override;
    virtual OTF2_DefReaderCallbacks * get_def_callbacks() const override;
    virtual OTF2_EvtReaderCallbacks * get_evt_callbacks() const override;
    virtual void set_current_location(const OTF2_LocationRef ref) override;
    virtual void * get_user_data() const override;
    TraceData * get_trace_data() const;
    DefaultCallbacks();
    virtual ~DefaultCallbacks();
};
#endif
