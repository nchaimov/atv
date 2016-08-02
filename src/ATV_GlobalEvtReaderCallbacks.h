#ifndef ATV_GLOBAL_EVT_READER_CALLBACKS_H
#define ATV_GLOBAL_EVT_READER_CALLBACKS_H

#include <stdint.h>
#include <otf2/OTF2_ErrorCodes.h>
#include <otf2/OTF2_GeneralDefinitions.h>
#include <otf2/OTF2_AttributeValue.h>
#include <otf2/OTF2_Definitions.h>
#include <otf2/OTF2_GlobalEvtReaderCallbacks.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Unknown( OTF2_LocationRef locationID,
    OTF2_TimeStamp time,
    void * userData,
    OTF2_AttributeList* attributeList);


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_BufferFlush ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_TimeStamp stopTime );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MeasurementOnOff ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MeasurementMode measurementMode );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Enter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Leave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiSend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIsend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIsendComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIrecvRequest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiRecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiIrecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiRequestTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiRequestCancelled ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_MpiCollectiveEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_CommRef communicator,
uint32_t root,
uint64_t sizeSent,
uint64_t sizeReceived );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t numberOfRequestedThreads );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_OmpTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_Metric ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MetricRef metric,
uint8_t numberOfMetrics,
const OTF2_Type* typeIDs,
const OTF2_MetricValue* metricValues );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ParameterString ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
OTF2_StringRef string );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ParameterInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
int64_t value );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ParameterUnsignedInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
uint64_t value );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaWinCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaWinDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaCollectiveEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
uint32_t root,
uint64_t bytesSent,
uint64_t bytesReceived );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaGroupSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
OTF2_GroupRef group );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaRequestLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaTryLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaSyncType syncType );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaWaitChange ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaPut ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaGet ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaAtomic ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaAtomicType type,
uint64_t bytesSent,
uint64_t bytesReceived,
uint64_t matchingId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpCompleteBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpCompleteNonBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_RmaOpCompleteRemote ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t numberOfRequestedThreads );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTeamBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTeamEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadWait ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_ThreadEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_CallingContextEnter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_CallingContextLeave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_CallingContextSample ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance,
OTF2_InterruptGeneratorRef interruptGenerator );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_TaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_TaskDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_TaskRunnable ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_AddDependence ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_SatisfyDependence ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataAcquire ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataRelease ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_EventCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_EventDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region,
uint64_t size );


OTF2_CallbackCode ATV_GlobalEvtReaderCallback_DataDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_GlobalEvtReaderCallbacks * ATV_CreateGlobalEvtReaderCallbacks(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* !OTF2_GLOBAL_EVT_READER_CALLBACKS_H */
