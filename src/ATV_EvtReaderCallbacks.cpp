
#include "ATV_EvtReaderCallbacks.h"
#include "trace_data.hpp"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OTF2_CallbackCode ATV_EvtReaderCallback_Unknown( OTF2_LocationRef locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void * userData,
    OTF2_AttributeList* attributeList) {
    
    return OTF2_CALLBACK_SUCCESS;    
}


OTF2_CallbackCode ATV_EvtReaderCallback_BufferFlush ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_TimeStamp stopTime ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MeasurementOnOff ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MeasurementMode measurementMode ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    const TraceData::EventType type = measurementMode == OTF2_MEASUREMENT_ON ? TraceData::EventType::MeasurementOn : TraceData::EventType::MeasurementOff;
    trace_data->put_event(locationID, type, time, event_position, TraceData::INVALID_REGION_REF, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_Enter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::Enter, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_Leave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::Leave, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiSend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIsend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIsendComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIrecvRequest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiRecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIrecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiRequestTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiRequestCancelled ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_MpiCollectiveEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_CommRef communicator,
uint32_t root,
uint64_t sizeSent,
uint64_t sizeReceived ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_OmpFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t numberOfRequestedThreads ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_OmpJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_OmpAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_OmpReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_OmpTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_OmpTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_OmpTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_Metric ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MetricRef metric,
uint8_t numberOfMetrics,
const OTF2_Type* typeIDs,
const OTF2_MetricValue* metricValues ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ParameterString ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
OTF2_StringRef string ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ParameterInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
int64_t value ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ParameterUnsignedInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
uint64_t value ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaWinCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaWinDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaCollectiveEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
uint32_t root,
uint64_t bytesSent,
uint64_t bytesReceived ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaGroupSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
OTF2_GroupRef group ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaRequestLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaTryLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaSyncType syncType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaWaitChange ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaPut ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaGet ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaAtomic ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaAtomicType type,
uint64_t bytesSent,
uint64_t bytesReceived,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpCompleteBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpCompleteNonBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpCompleteRemote ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t numberOfRequestedThreads ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTeamBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTeamEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadWait ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_CallingContextEnter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_CallingContextLeave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_CallingContextSample ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance,
OTF2_InterruptGeneratorRef interruptGenerator ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_TaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::TaskCreate, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_TaskDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::TaskDestroy, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_TaskRunnable ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::TaskRunnable, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_AddDependence ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::AddDependence, time, event_position, src, dest, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_SatisfyDependence ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::SatisfyDependence, time, event_position, src, dest, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_DataAcquire ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::DataAcquire, time, event_position, task, data, size);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_DataRelease ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::DataRelease, time, event_position, task, data, size);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_EventCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::EventCreate, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_EventDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::EventDestroy, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_DataCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region,
uint64_t size ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::DataCreate, time, event_position, region, TraceData::INVALID_REGION_REF, size);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_EvtReaderCallback_DataDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);                       
    trace_data->put_event(locationID, TraceData::EventType::DataDestroy, time, event_position, region, TraceData::INVALID_REGION_REF, TraceData::INVALID_SIZE);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_EvtReaderCallbacks * ATV_CreateEvtReaderCallbacks(void) {
    OTF2_EvtReaderCallbacks* evt_callbacks = OTF2_EvtReaderCallbacks_New();
    //OTF2_EvtReaderCallbacks_SetUnknownCallback( evt_callbacks, ATV_EvtReaderCallback_Unknown );
    //OTF2_EvtReaderCallbacks_SetBufferFlushCallback( evt_callbacks, ATV_EvtReaderCallback_BufferFlush );
    OTF2_EvtReaderCallbacks_SetMeasurementOnOffCallback( evt_callbacks, ATV_EvtReaderCallback_MeasurementOnOff );
    OTF2_EvtReaderCallbacks_SetEnterCallback( evt_callbacks, ATV_EvtReaderCallback_Enter );
    OTF2_EvtReaderCallbacks_SetLeaveCallback( evt_callbacks, ATV_EvtReaderCallback_Leave );
    //OTF2_EvtReaderCallbacks_SetMpiSendCallback( evt_callbacks, ATV_EvtReaderCallback_MpiSend );
    //OTF2_EvtReaderCallbacks_SetMpiIsendCallback( evt_callbacks, ATV_EvtReaderCallback_MpiIsend );
    //OTF2_EvtReaderCallbacks_SetMpiIsendCompleteCallback( evt_callbacks, ATV_EvtReaderCallback_MpiIsendComplete );
    //OTF2_EvtReaderCallbacks_SetMpiIrecvRequestCallback( evt_callbacks, ATV_EvtReaderCallback_MpiIrecvRequest );
    //OTF2_EvtReaderCallbacks_SetMpiRecvCallback( evt_callbacks, ATV_EvtReaderCallback_MpiRecv );
    //OTF2_EvtReaderCallbacks_SetMpiIrecvCallback( evt_callbacks, ATV_EvtReaderCallback_MpiIrecv );
    //OTF2_EvtReaderCallbacks_SetMpiRequestTestCallback( evt_callbacks, ATV_EvtReaderCallback_MpiRequestTest );
    //OTF2_EvtReaderCallbacks_SetMpiRequestCancelledCallback( evt_callbacks, ATV_EvtReaderCallback_MpiRequestCancelled );
    //OTF2_EvtReaderCallbacks_SetMpiCollectiveBeginCallback( evt_callbacks, ATV_EvtReaderCallback_MpiCollectiveBegin );
    //OTF2_EvtReaderCallbacks_SetMpiCollectiveEndCallback( evt_callbacks, ATV_EvtReaderCallback_MpiCollectiveEnd );
    //OTF2_EvtReaderCallbacks_SetOmpForkCallback( evt_callbacks, ATV_EvtReaderCallback_OmpFork );
    //OTF2_EvtReaderCallbacks_SetOmpJoinCallback( evt_callbacks, ATV_EvtReaderCallback_OmpJoin );
    //OTF2_EvtReaderCallbacks_SetOmpAcquireLockCallback( evt_callbacks, ATV_EvtReaderCallback_OmpAcquireLock );
    //OTF2_EvtReaderCallbacks_SetOmpReleaseLockCallback( evt_callbacks, ATV_EvtReaderCallback_OmpReleaseLock );
    //OTF2_EvtReaderCallbacks_SetOmpTaskCreateCallback( evt_callbacks, ATV_EvtReaderCallback_OmpTaskCreate );
    //OTF2_EvtReaderCallbacks_SetOmpTaskSwitchCallback( evt_callbacks, ATV_EvtReaderCallback_OmpTaskSwitch );
    //OTF2_EvtReaderCallbacks_SetOmpTaskCompleteCallback( evt_callbacks, ATV_EvtReaderCallback_OmpTaskComplete );
    //OTF2_EvtReaderCallbacks_SetMetricCallback( evt_callbacks, ATV_EvtReaderCallback_Metric );
    //OTF2_EvtReaderCallbacks_SetParameterStringCallback( evt_callbacks, ATV_EvtReaderCallback_ParameterString );
    //OTF2_EvtReaderCallbacks_SetParameterIntCallback( evt_callbacks, ATV_EvtReaderCallback_ParameterInt );
    //OTF2_EvtReaderCallbacks_SetParameterUnsignedIntCallback( evt_callbacks, ATV_EvtReaderCallback_ParameterUnsignedInt );
    //OTF2_EvtReaderCallbacks_SetRmaWinCreateCallback( evt_callbacks, ATV_EvtReaderCallback_RmaWinCreate );
    //OTF2_EvtReaderCallbacks_SetRmaWinDestroyCallback( evt_callbacks, ATV_EvtReaderCallback_RmaWinDestroy );
    //OTF2_EvtReaderCallbacks_SetRmaCollectiveBeginCallback( evt_callbacks, ATV_EvtReaderCallback_RmaCollectiveBegin );
    //OTF2_EvtReaderCallbacks_SetRmaCollectiveEndCallback( evt_callbacks, ATV_EvtReaderCallback_RmaCollectiveEnd );
    //OTF2_EvtReaderCallbacks_SetRmaGroupSyncCallback( evt_callbacks, ATV_EvtReaderCallback_RmaGroupSync );
    //OTF2_EvtReaderCallbacks_SetRmaRequestLockCallback( evt_callbacks, ATV_EvtReaderCallback_RmaRequestLock );
    //OTF2_EvtReaderCallbacks_SetRmaAcquireLockCallback( evt_callbacks, ATV_EvtReaderCallback_RmaAcquireLock );
    //OTF2_EvtReaderCallbacks_SetRmaTryLockCallback( evt_callbacks, ATV_EvtReaderCallback_RmaTryLock );
    //OTF2_EvtReaderCallbacks_SetRmaReleaseLockCallback( evt_callbacks, ATV_EvtReaderCallback_RmaReleaseLock );
    //OTF2_EvtReaderCallbacks_SetRmaSyncCallback( evt_callbacks, ATV_EvtReaderCallback_RmaSync );
    //OTF2_EvtReaderCallbacks_SetRmaWaitChangeCallback( evt_callbacks, ATV_EvtReaderCallback_RmaWaitChange );
    //OTF2_EvtReaderCallbacks_SetRmaPutCallback( evt_callbacks, ATV_EvtReaderCallback_RmaPut );
    //OTF2_EvtReaderCallbacks_SetRmaGetCallback( evt_callbacks, ATV_EvtReaderCallback_RmaGet );
    //OTF2_EvtReaderCallbacks_SetRmaAtomicCallback( evt_callbacks, ATV_EvtReaderCallback_RmaAtomic );
    //OTF2_EvtReaderCallbacks_SetRmaOpCompleteBlockingCallback( evt_callbacks, ATV_EvtReaderCallback_RmaOpCompleteBlocking );
    //OTF2_EvtReaderCallbacks_SetRmaOpCompleteNonBlockingCallback( evt_callbacks, ATV_EvtReaderCallback_RmaOpCompleteNonBlocking );
    //OTF2_EvtReaderCallbacks_SetRmaOpTestCallback( evt_callbacks, ATV_EvtReaderCallback_RmaOpTest );
    //OTF2_EvtReaderCallbacks_SetRmaOpCompleteRemoteCallback( evt_callbacks, ATV_EvtReaderCallback_RmaOpCompleteRemote );
    //OTF2_EvtReaderCallbacks_SetThreadForkCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadFork );
    //OTF2_EvtReaderCallbacks_SetThreadJoinCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadJoin );
    //OTF2_EvtReaderCallbacks_SetThreadTeamBeginCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadTeamBegin );
    //OTF2_EvtReaderCallbacks_SetThreadTeamEndCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadTeamEnd );
    //OTF2_EvtReaderCallbacks_SetThreadAcquireLockCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadAcquireLock );
    //OTF2_EvtReaderCallbacks_SetThreadReleaseLockCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadReleaseLock );
    //OTF2_EvtReaderCallbacks_SetThreadTaskCreateCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadTaskCreate );
    //OTF2_EvtReaderCallbacks_SetThreadTaskSwitchCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadTaskSwitch );
    //OTF2_EvtReaderCallbacks_SetThreadTaskCompleteCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadTaskComplete );
    //OTF2_EvtReaderCallbacks_SetThreadCreateCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadCreate );
    //OTF2_EvtReaderCallbacks_SetThreadBeginCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadBegin );
    //OTF2_EvtReaderCallbacks_SetThreadWaitCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadWait );
    //OTF2_EvtReaderCallbacks_SetThreadEndCallback( evt_callbacks, ATV_EvtReaderCallback_ThreadEnd );
    //OTF2_EvtReaderCallbacks_SetCallingContextEnterCallback( evt_callbacks, ATV_EvtReaderCallback_CallingContextEnter );
    //OTF2_EvtReaderCallbacks_SetCallingContextLeaveCallback( evt_callbacks, ATV_EvtReaderCallback_CallingContextLeave );
    //OTF2_EvtReaderCallbacks_SetCallingContextSampleCallback( evt_callbacks, ATV_EvtReaderCallback_CallingContextSample );
    OTF2_EvtReaderCallbacks_SetTaskCreateCallback( evt_callbacks, ATV_EvtReaderCallback_TaskCreate );
    OTF2_EvtReaderCallbacks_SetTaskDestroyCallback( evt_callbacks, ATV_EvtReaderCallback_TaskDestroy );
    OTF2_EvtReaderCallbacks_SetTaskRunnableCallback( evt_callbacks, ATV_EvtReaderCallback_TaskRunnable );
    OTF2_EvtReaderCallbacks_SetAddDependenceCallback( evt_callbacks, ATV_EvtReaderCallback_AddDependence );
    OTF2_EvtReaderCallbacks_SetSatisfyDependenceCallback( evt_callbacks, ATV_EvtReaderCallback_SatisfyDependence );
    OTF2_EvtReaderCallbacks_SetDataAcquireCallback( evt_callbacks, ATV_EvtReaderCallback_DataAcquire );
    OTF2_EvtReaderCallbacks_SetDataReleaseCallback( evt_callbacks, ATV_EvtReaderCallback_DataRelease );
    OTF2_EvtReaderCallbacks_SetEventCreateCallback( evt_callbacks, ATV_EvtReaderCallback_EventCreate );
    OTF2_EvtReaderCallbacks_SetEventDestroyCallback( evt_callbacks, ATV_EvtReaderCallback_EventDestroy );
    OTF2_EvtReaderCallbacks_SetDataCreateCallback( evt_callbacks, ATV_EvtReaderCallback_DataCreate );
    OTF2_EvtReaderCallbacks_SetDataDestroyCallback( evt_callbacks, ATV_EvtReaderCallback_DataDestroy );

    return evt_callbacks;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */


