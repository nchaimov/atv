
#include "ATV_GlobalEvtReaderCallbacks.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Unknown( OTF2_LocationRef locationID,
    OTF2_TimeStamp time,
    void * userData,
    OTF2_AttributeList* attributeList) {

    return OTF2_CALLBACK_SUCCESS;    
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_BufferFlush ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_TimeStamp stopTime ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MeasurementOnOff ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MeasurementMode measurementMode ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Enter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Leave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiSend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIsend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIsendComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIrecvRequest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiRecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIrecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiRequestTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiRequestCancelled ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiCollectiveEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_CommRef communicator,
uint32_t root,
uint64_t sizeSent,
uint64_t sizeReceived ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t numberOfRequestedThreads ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Metric ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MetricRef metric,
uint8_t numberOfMetrics,
const OTF2_Type* typeIDs,
const OTF2_MetricValue* metricValues ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ParameterString ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
OTF2_StringRef string ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ParameterInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
int64_t value ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ParameterUnsignedInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
uint64_t value ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaWinCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaWinDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaCollectiveEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
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


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaGroupSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
OTF2_GroupRef group ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaRequestLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaTryLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaSyncType syncType ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaWaitChange ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaPut ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaGet ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaAtomic ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
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


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpCompleteBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpCompleteNonBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpCompleteRemote ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t numberOfRequestedThreads ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTeamBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTeamEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadWait ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_CallingContextEnter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_CallingContextLeave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_CallingContextSample ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance,
OTF2_InterruptGeneratorRef interruptGenerator ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_TaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_TaskDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_TaskRunnable ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_AddDependence ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_SatisfyDependence ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataAcquire ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataRelease ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_EventCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_EventDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region,
uint64_t size ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region ) {

    return OTF2_CALLBACK_SUCCESS;
}


OTF2_GlobalEvtReaderCallbacks * ATV_CreateGlobalEvtReaderCallbacks(void) {
    OTF2_GlobalEvtReaderCallbacks* evt_callbacks = OTF2_GlobalEvtReaderCallbacks_New();
    OTF2_GlobalEvtReaderCallbacks_SetUnknownCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_Unknown );
    OTF2_GlobalEvtReaderCallbacks_SetBufferFlushCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_BufferFlush );
    OTF2_GlobalEvtReaderCallbacks_SetMeasurementOnOffCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MeasurementOnOff );
    OTF2_GlobalEvtReaderCallbacks_SetEnterCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_Enter );
    OTF2_GlobalEvtReaderCallbacks_SetLeaveCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_Leave );
    OTF2_GlobalEvtReaderCallbacks_SetMpiSendCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiSend );
    OTF2_GlobalEvtReaderCallbacks_SetMpiIsendCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiIsend );
    OTF2_GlobalEvtReaderCallbacks_SetMpiIsendCompleteCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiIsendComplete );
    OTF2_GlobalEvtReaderCallbacks_SetMpiIrecvRequestCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiIrecvRequest );
    OTF2_GlobalEvtReaderCallbacks_SetMpiRecvCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiRecv );
    OTF2_GlobalEvtReaderCallbacks_SetMpiIrecvCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiIrecv );
    OTF2_GlobalEvtReaderCallbacks_SetMpiRequestTestCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiRequestTest );
    OTF2_GlobalEvtReaderCallbacks_SetMpiRequestCancelledCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiRequestCancelled );
    OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveBeginCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiCollectiveBegin );
    OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveEndCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_MpiCollectiveEnd );
    OTF2_GlobalEvtReaderCallbacks_SetOmpForkCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_OmpFork );
    OTF2_GlobalEvtReaderCallbacks_SetOmpJoinCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_OmpJoin );
    OTF2_GlobalEvtReaderCallbacks_SetOmpAcquireLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_OmpAcquireLock );
    OTF2_GlobalEvtReaderCallbacks_SetOmpReleaseLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_OmpReleaseLock );
    OTF2_GlobalEvtReaderCallbacks_SetOmpTaskCreateCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_OmpTaskCreate );
    OTF2_GlobalEvtReaderCallbacks_SetOmpTaskSwitchCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_OmpTaskSwitch );
    OTF2_GlobalEvtReaderCallbacks_SetOmpTaskCompleteCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_OmpTaskComplete );
    OTF2_GlobalEvtReaderCallbacks_SetMetricCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_Metric );
    OTF2_GlobalEvtReaderCallbacks_SetParameterStringCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ParameterString );
    OTF2_GlobalEvtReaderCallbacks_SetParameterIntCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ParameterInt );
    OTF2_GlobalEvtReaderCallbacks_SetParameterUnsignedIntCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ParameterUnsignedInt );
    OTF2_GlobalEvtReaderCallbacks_SetRmaWinCreateCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaWinCreate );
    OTF2_GlobalEvtReaderCallbacks_SetRmaWinDestroyCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaWinDestroy );
    OTF2_GlobalEvtReaderCallbacks_SetRmaCollectiveBeginCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaCollectiveBegin );
    OTF2_GlobalEvtReaderCallbacks_SetRmaCollectiveEndCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaCollectiveEnd );
    OTF2_GlobalEvtReaderCallbacks_SetRmaGroupSyncCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaGroupSync );
    OTF2_GlobalEvtReaderCallbacks_SetRmaRequestLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaRequestLock );
    OTF2_GlobalEvtReaderCallbacks_SetRmaAcquireLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaAcquireLock );
    OTF2_GlobalEvtReaderCallbacks_SetRmaTryLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaTryLock );
    OTF2_GlobalEvtReaderCallbacks_SetRmaReleaseLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaReleaseLock );
    OTF2_GlobalEvtReaderCallbacks_SetRmaSyncCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaSync );
    OTF2_GlobalEvtReaderCallbacks_SetRmaWaitChangeCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaWaitChange );
    OTF2_GlobalEvtReaderCallbacks_SetRmaPutCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaPut );
    OTF2_GlobalEvtReaderCallbacks_SetRmaGetCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaGet );
    OTF2_GlobalEvtReaderCallbacks_SetRmaAtomicCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaAtomic );
    OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteBlockingCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaOpCompleteBlocking );
    OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteNonBlockingCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaOpCompleteNonBlocking );
    OTF2_GlobalEvtReaderCallbacks_SetRmaOpTestCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaOpTest );
    OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteRemoteCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_RmaOpCompleteRemote );
    OTF2_GlobalEvtReaderCallbacks_SetThreadForkCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadFork );
    OTF2_GlobalEvtReaderCallbacks_SetThreadJoinCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadJoin );
    OTF2_GlobalEvtReaderCallbacks_SetThreadTeamBeginCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadTeamBegin );
    OTF2_GlobalEvtReaderCallbacks_SetThreadTeamEndCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadTeamEnd );
    OTF2_GlobalEvtReaderCallbacks_SetThreadAcquireLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadAcquireLock );
    OTF2_GlobalEvtReaderCallbacks_SetThreadReleaseLockCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadReleaseLock );
    OTF2_GlobalEvtReaderCallbacks_SetThreadTaskCreateCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadTaskCreate );
    OTF2_GlobalEvtReaderCallbacks_SetThreadTaskSwitchCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadTaskSwitch );
    OTF2_GlobalEvtReaderCallbacks_SetThreadTaskCompleteCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadTaskComplete );
    OTF2_GlobalEvtReaderCallbacks_SetThreadCreateCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadCreate );
    OTF2_GlobalEvtReaderCallbacks_SetThreadBeginCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadBegin );
    OTF2_GlobalEvtReaderCallbacks_SetThreadWaitCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadWait );
    OTF2_GlobalEvtReaderCallbacks_SetThreadEndCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_ThreadEnd );
    OTF2_GlobalEvtReaderCallbacks_SetCallingContextEnterCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_CallingContextEnter );
    OTF2_GlobalEvtReaderCallbacks_SetCallingContextLeaveCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_CallingContextLeave );
    OTF2_GlobalEvtReaderCallbacks_SetCallingContextSampleCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_CallingContextSample );
    OTF2_GlobalEvtReaderCallbacks_SetTaskCreateCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_TaskCreate );
    OTF2_GlobalEvtReaderCallbacks_SetTaskDestroyCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_TaskDestroy );
    OTF2_GlobalEvtReaderCallbacks_SetTaskRunnableCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_TaskRunnable );
    OTF2_GlobalEvtReaderCallbacks_SetAddDependenceCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_AddDependence );
    OTF2_GlobalEvtReaderCallbacks_SetSatisfyDependenceCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_SatisfyDependence );
    OTF2_GlobalEvtReaderCallbacks_SetDataAcquireCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_DataAcquire );
    OTF2_GlobalEvtReaderCallbacks_SetDataReleaseCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_DataRelease );
    OTF2_GlobalEvtReaderCallbacks_SetEventCreateCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_EventCreate );
    OTF2_GlobalEvtReaderCallbacks_SetEventDestroyCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_EventDestroy );
    OTF2_GlobalEvtReaderCallbacks_SetDataCreateCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_DataCreate );
    OTF2_GlobalEvtReaderCallbacks_SetDataDestroyCallback( evt_callbacks, ATV_GlobalEvtReaderCallback_DataDestroy );

    return evt_callbacks;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */


