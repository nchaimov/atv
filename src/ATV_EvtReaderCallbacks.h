#ifndef ATV_EVT_READER_CALLBACKS_H
#define ATV_EVT_READER_CALLBACKS_H

#include <stdint.h>
#include <otf2/OTF2_ErrorCodes.h>
#include <otf2/OTF2_GeneralDefinitions.h>
#include <otf2/OTF2_AttributeValue.h>
#include <otf2/OTF2_Definitions.h>
#include <otf2/OTF2_EvtReaderCallbacks.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OTF2_CallbackCode ATV_EvtReaderCallback_Unknown( OTF2_LocationRef locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void * userData,
    OTF2_AttributeList* attributeList);


OTF2_CallbackCode ATV_EvtReaderCallback_BufferFlush ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_TimeStamp stopTime );


OTF2_CallbackCode ATV_EvtReaderCallback_MeasurementOnOff ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MeasurementMode measurementMode );


OTF2_CallbackCode ATV_EvtReaderCallback_Enter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_EvtReaderCallback_Leave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiSend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIsend ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIsendComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIrecvRequest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiRecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiIrecv ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiRequestTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiRequestCancelled ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t requestID );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList );


OTF2_CallbackCode ATV_EvtReaderCallback_MpiCollectiveEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_CommRef communicator,
uint32_t root,
uint64_t sizeSent,
uint64_t sizeReceived );


OTF2_CallbackCode ATV_EvtReaderCallback_OmpFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t numberOfRequestedThreads );


OTF2_CallbackCode ATV_EvtReaderCallback_OmpJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList );


OTF2_CallbackCode ATV_EvtReaderCallback_OmpAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_EvtReaderCallback_OmpReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_EvtReaderCallback_OmpTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID );


OTF2_CallbackCode ATV_EvtReaderCallback_OmpTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID );


OTF2_CallbackCode ATV_EvtReaderCallback_OmpTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
uint64_t taskID );


OTF2_CallbackCode ATV_EvtReaderCallback_Metric ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_MetricRef metric,
uint8_t numberOfMetrics,
const OTF2_Type* typeIDs,
const OTF2_MetricValue* metricValues );


OTF2_CallbackCode ATV_EvtReaderCallback_ParameterString ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
OTF2_StringRef string );


OTF2_CallbackCode ATV_EvtReaderCallback_ParameterInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
int64_t value );


OTF2_CallbackCode ATV_EvtReaderCallback_ParameterUnsignedInt ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
uint64_t value );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaWinCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaWinDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaCollectiveBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList );


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
uint64_t bytesReceived );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaGroupSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
OTF2_GroupRef group );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaRequestLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaTryLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaSync ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaSyncType syncType );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaWaitChange ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaPut ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaGet ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId );


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
uint64_t matchingId );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpCompleteBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpCompleteNonBlocking ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpTest ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_EvtReaderCallback_RmaOpCompleteRemote ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadFork ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t numberOfRequestedThreads );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadJoin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTeamBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTeamEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadAcquireLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadReleaseLock ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTaskSwitch ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadTaskComplete ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadBegin ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadWait ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_EvtReaderCallback_ThreadEnd ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


OTF2_CallbackCode ATV_EvtReaderCallback_CallingContextEnter ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance );


OTF2_CallbackCode ATV_EvtReaderCallback_CallingContextLeave ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext );


OTF2_CallbackCode ATV_EvtReaderCallback_CallingContextSample ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance,
OTF2_InterruptGeneratorRef interruptGenerator );


OTF2_CallbackCode ATV_EvtReaderCallback_TaskCreate ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_EvtReaderCallback_TaskDestroy ( OTF2_LocationRef  locationID,
    OTF2_TimeStamp time,
    uint64_t event_position,
    void* userData,
    OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


OTF2_EvtReaderCallbacks * ATV_CreateEvtReaderCallbacks(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* !OTF2_EVT_READER_CALLBACKS_H */
