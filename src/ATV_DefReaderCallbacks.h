#ifndef ATV_DEF_READER_CALLBACKS_H
#define ATV_DEF_READER_CALLBACKS_H

#include <stdint.h>
#include <otf2/OTF2_ErrorCodes.h>
#include <otf2/OTF2_GeneralDefinitions.h>
#include <otf2/OTF2_AttributeValue.h>
#include <otf2/OTF2_Definitions.h>
#include <otf2/OTF2_DefReaderCallbacks.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OTF2_CallbackCode ATV_DefReaderCallback_Unknown( void * userData );


OTF2_CallbackCode ATV_DefReaderCallback_MappingTable ( void* userData ,
OTF2_MappingType mappingType,
const OTF2_IdMap* idMap );


OTF2_CallbackCode ATV_DefReaderCallback_ClockOffset ( void* userData ,
OTF2_TimeStamp time,
int64_t offset,
double standardDeviation );


OTF2_CallbackCode ATV_DefReaderCallback_String ( void* userData ,
OTF2_StringRef self,
const char* string );


OTF2_CallbackCode ATV_DefReaderCallback_Attribute ( void* userData ,
OTF2_AttributeRef self,
OTF2_StringRef name,
OTF2_StringRef description,
OTF2_Type type );


OTF2_CallbackCode ATV_DefReaderCallback_SystemTreeNode ( void* userData ,
OTF2_SystemTreeNodeRef self,
OTF2_StringRef name,
OTF2_StringRef className,
OTF2_SystemTreeNodeRef parent );


OTF2_CallbackCode ATV_DefReaderCallback_LocationGroup ( void* userData ,
OTF2_LocationGroupRef self,
OTF2_StringRef name,
OTF2_LocationGroupType locationGroupType,
OTF2_SystemTreeNodeRef systemTreeParent );


OTF2_CallbackCode ATV_DefReaderCallback_Location ( void* userData ,
OTF2_LocationRef self,
OTF2_StringRef name,
OTF2_LocationType locationType,
uint64_t numberOfEvents,
OTF2_LocationGroupRef locationGroup );


OTF2_CallbackCode ATV_DefReaderCallback_Region ( void* userData ,
OTF2_RegionRef self,
OTF2_StringRef name,
OTF2_StringRef canonicalName,
OTF2_StringRef description,
OTF2_RegionRole regionRole,
OTF2_Paradigm paradigm,
OTF2_RegionFlag regionFlags,
OTF2_StringRef sourceFile,
uint32_t beginLineNumber,
uint32_t endLineNumber );


OTF2_CallbackCode ATV_DefReaderCallback_Callsite ( void* userData ,
OTF2_CallsiteRef self,
OTF2_StringRef sourceFile,
uint32_t lineNumber,
OTF2_RegionRef enteredRegion,
OTF2_RegionRef leftRegion );


OTF2_CallbackCode ATV_DefReaderCallback_Callpath ( void* userData ,
OTF2_CallpathRef self,
OTF2_CallpathRef parent,
OTF2_RegionRef region );


OTF2_CallbackCode ATV_DefReaderCallback_Group ( void* userData ,
OTF2_GroupRef self,
OTF2_StringRef name,
OTF2_GroupType groupType,
OTF2_Paradigm paradigm,
OTF2_GroupFlag groupFlags,
uint32_t numberOfMembers,
const uint64_t* members );


OTF2_CallbackCode ATV_DefReaderCallback_MetricMember ( void* userData ,
OTF2_MetricMemberRef self,
OTF2_StringRef name,
OTF2_StringRef description,
OTF2_MetricType metricType,
OTF2_MetricMode metricMode,
OTF2_Type valueType,
OTF2_Base base,
int64_t exponent,
OTF2_StringRef unit );


OTF2_CallbackCode ATV_DefReaderCallback_MetricClass ( void* userData ,
OTF2_MetricRef self,
uint8_t numberOfMetrics,
const OTF2_MetricMemberRef* metricMembers,
OTF2_MetricOccurrence metricOccurrence,
OTF2_RecorderKind recorderKind );


OTF2_CallbackCode ATV_DefReaderCallback_MetricInstance ( void* userData ,
OTF2_MetricRef self,
OTF2_MetricRef metricClass,
OTF2_LocationRef recorder,
OTF2_MetricScope metricScope,
uint64_t scope );


OTF2_CallbackCode ATV_DefReaderCallback_Comm ( void* userData ,
OTF2_CommRef self,
OTF2_StringRef name,
OTF2_GroupRef group,
OTF2_CommRef parent );


OTF2_CallbackCode ATV_DefReaderCallback_Parameter ( void* userData ,
OTF2_ParameterRef self,
OTF2_StringRef name,
OTF2_ParameterType parameterType );


OTF2_CallbackCode ATV_DefReaderCallback_RmaWin ( void* userData ,
OTF2_RmaWinRef self,
OTF2_StringRef name,
OTF2_CommRef comm );


OTF2_CallbackCode ATV_DefReaderCallback_MetricClassRecorder ( void* userData ,
OTF2_MetricRef metricClass,
OTF2_LocationRef recorder );


OTF2_CallbackCode ATV_DefReaderCallback_SystemTreeNodeProperty ( void* userData ,
OTF2_SystemTreeNodeRef systemTreeNode,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value );


OTF2_CallbackCode ATV_DefReaderCallback_SystemTreeNodeDomain ( void* userData ,
OTF2_SystemTreeNodeRef systemTreeNode,
OTF2_SystemTreeDomain systemTreeDomain );


OTF2_CallbackCode ATV_DefReaderCallback_LocationGroupProperty ( void* userData ,
OTF2_LocationGroupRef locationGroup,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value );


OTF2_CallbackCode ATV_DefReaderCallback_LocationProperty ( void* userData ,
OTF2_LocationRef location,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value );


OTF2_CallbackCode ATV_DefReaderCallback_CartDimension ( void* userData ,
OTF2_CartDimensionRef self,
OTF2_StringRef name,
uint32_t size,
OTF2_CartPeriodicity cartPeriodicity );


OTF2_CallbackCode ATV_DefReaderCallback_CartTopology ( void* userData ,
OTF2_CartTopologyRef self,
OTF2_StringRef name,
OTF2_CommRef communicator,
uint8_t numberOfDimensions,
const OTF2_CartDimensionRef* cartDimensions );


OTF2_CallbackCode ATV_DefReaderCallback_CartCoordinate ( void* userData ,
OTF2_CartTopologyRef cartTopology,
uint32_t rank,
uint8_t numberOfDimensions,
const uint32_t* coordinates );


OTF2_CallbackCode ATV_DefReaderCallback_SourceCodeLocation ( void* userData ,
OTF2_SourceCodeLocationRef self,
OTF2_StringRef file,
uint32_t lineNumber );


OTF2_CallbackCode ATV_DefReaderCallback_CallingContext ( void* userData ,
OTF2_CallingContextRef self,
OTF2_RegionRef region,
OTF2_SourceCodeLocationRef sourceCodeLocation,
OTF2_CallingContextRef parent );


OTF2_CallbackCode ATV_DefReaderCallback_CallingContextProperty ( void* userData ,
OTF2_CallingContextRef callingContext,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value );


OTF2_CallbackCode ATV_DefReaderCallback_InterruptGenerator ( void* userData ,
OTF2_InterruptGeneratorRef self,
OTF2_StringRef name,
OTF2_InterruptGeneratorMode interruptGeneratorMode,
OTF2_Base base,
int64_t exponent,
uint64_t period );


OTF2_DefReaderCallbacks * ATV_CreateDefReaderCallbacks(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* !OTF2_GLOBAL_DEF_READER_CALLBACKS_H */
