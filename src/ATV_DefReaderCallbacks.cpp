
#include <iostream>

#include "ATV_DefReaderCallbacks.h"
#include "trace_data.hpp"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OTF2_CallbackCode ATV_DefReaderCallback_Unknown( void * userData ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_MappingTable ( void* userData ,
OTF2_MappingType mappingType,
const OTF2_IdMap* idMap ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_ClockOffset ( void* userData ,
OTF2_TimeStamp time,
int64_t offset,
double standardDeviation ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_String ( void* userData ,
OTF2_StringRef self,
const char* string ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);
    const OTF2_LocationRef loc = trace_data->get_current_location();
    trace_data->put_string(loc, self, string);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_Attribute ( void* userData ,
OTF2_AttributeRef self,
OTF2_StringRef name,
OTF2_StringRef description,
OTF2_Type type ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_SystemTreeNode ( void* userData ,
OTF2_SystemTreeNodeRef self,
OTF2_StringRef name,
OTF2_StringRef className,
OTF2_SystemTreeNodeRef parent ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);
    const OTF2_LocationRef loc = trace_data->get_current_location();
    trace_data->put_system_tree_node(loc, self, name, className, parent);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_LocationGroup ( void* userData ,
OTF2_LocationGroupRef self,
OTF2_StringRef name,
OTF2_LocationGroupType locationGroupType,
OTF2_SystemTreeNodeRef systemTreeParent ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);
    const OTF2_LocationRef loc = trace_data->get_current_location();
    trace_data->put_location_group(loc, self, name, locationGroupType, systemTreeParent);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_Location ( void* userData ,
OTF2_LocationRef self,
OTF2_StringRef name,
OTF2_LocationType locationType,
uint64_t numberOfEvents,
OTF2_LocationGroupRef locationGroup ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);
    trace_data->put_location(self, name, locationType, numberOfEvents, locationGroup);
    return OTF2_CALLBACK_SUCCESS;
}


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
uint32_t endLineNumber ) {
    TraceData * trace_data = static_cast<TraceData *>(userData);
    const OTF2_LocationRef loc = trace_data->get_current_location();
    trace_data->put_region(loc, self, name, canonicalName, description, regionRole, paradigm, regionFlags, sourceFile, beginLineNumber, endLineNumber);
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_Callsite ( void* userData ,
OTF2_CallsiteRef self,
OTF2_StringRef sourceFile,
uint32_t lineNumber,
OTF2_RegionRef enteredRegion,
OTF2_RegionRef leftRegion ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_Callpath ( void* userData ,
OTF2_CallpathRef self,
OTF2_CallpathRef parent,
OTF2_RegionRef region ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_Group ( void* userData ,
OTF2_GroupRef self,
OTF2_StringRef name,
OTF2_GroupType groupType,
OTF2_Paradigm paradigm,
OTF2_GroupFlag groupFlags,
uint32_t numberOfMembers,
const uint64_t* members ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_MetricMember ( void* userData ,
OTF2_MetricMemberRef self,
OTF2_StringRef name,
OTF2_StringRef description,
OTF2_MetricType metricType,
OTF2_MetricMode metricMode,
OTF2_Type valueType,
OTF2_Base base,
int64_t exponent,
OTF2_StringRef unit ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_MetricClass ( void* userData ,
OTF2_MetricRef self,
uint8_t numberOfMetrics,
const OTF2_MetricMemberRef* metricMembers,
OTF2_MetricOccurrence metricOccurrence,
OTF2_RecorderKind recorderKind ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_MetricInstance ( void* userData ,
OTF2_MetricRef self,
OTF2_MetricRef metricClass,
OTF2_LocationRef recorder,
OTF2_MetricScope metricScope,
uint64_t scope ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_Comm ( void* userData ,
OTF2_CommRef self,
OTF2_StringRef name,
OTF2_GroupRef group,
OTF2_CommRef parent ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_Parameter ( void* userData ,
OTF2_ParameterRef self,
OTF2_StringRef name,
OTF2_ParameterType parameterType ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_RmaWin ( void* userData ,
OTF2_RmaWinRef self,
OTF2_StringRef name,
OTF2_CommRef comm ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_MetricClassRecorder ( void* userData ,
OTF2_MetricRef metricClass,
OTF2_LocationRef recorder ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_SystemTreeNodeProperty ( void* userData ,
OTF2_SystemTreeNodeRef systemTreeNode,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_SystemTreeNodeDomain ( void* userData ,
OTF2_SystemTreeNodeRef systemTreeNode,
OTF2_SystemTreeDomain systemTreeDomain ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_LocationGroupProperty ( void* userData ,
OTF2_LocationGroupRef locationGroup,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_LocationProperty ( void* userData ,
OTF2_LocationRef location,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_CartDimension ( void* userData ,
OTF2_CartDimensionRef self,
OTF2_StringRef name,
uint32_t size,
OTF2_CartPeriodicity cartPeriodicity ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_CartTopology ( void* userData ,
OTF2_CartTopologyRef self,
OTF2_StringRef name,
OTF2_CommRef communicator,
uint8_t numberOfDimensions,
const OTF2_CartDimensionRef* cartDimensions ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_CartCoordinate ( void* userData ,
OTF2_CartTopologyRef cartTopology,
uint32_t rank,
uint8_t numberOfDimensions,
const uint32_t* coordinates ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_SourceCodeLocation ( void* userData ,
OTF2_SourceCodeLocationRef self,
OTF2_StringRef file,
uint32_t lineNumber ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_CallingContext ( void* userData ,
OTF2_CallingContextRef self,
OTF2_RegionRef region,
OTF2_SourceCodeLocationRef sourceCodeLocation,
OTF2_CallingContextRef parent ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_CallingContextProperty ( void* userData ,
OTF2_CallingContextRef callingContext,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_DefReaderCallback_InterruptGenerator ( void* userData ,
OTF2_InterruptGeneratorRef self,
OTF2_StringRef name,
OTF2_InterruptGeneratorMode interruptGeneratorMode,
OTF2_Base base,
int64_t exponent,
uint64_t period ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_DefReaderCallbacks * ATV_CreateDefReaderCallbacks(void) {
    OTF2_DefReaderCallbacks * def_callbacks = OTF2_DefReaderCallbacks_New();
    //OTF2_DefReaderCallbacks_SetUnknownCallback(def_callbacks, ATV_DefReaderCallback_Unknown);
    //OTF2_DefReaderCallbacks_SetMappingTableCallback( def_callbacks, ATV_DefReaderCallback_MappingTable );
    //OTF2_DefReaderCallbacks_SetClockOffsetCallback( def_callbacks, ATV_DefReaderCallback_ClockOffset );
    OTF2_DefReaderCallbacks_SetStringCallback( def_callbacks, ATV_DefReaderCallback_String );
    //OTF2_DefReaderCallbacks_SetAttributeCallback( def_callbacks, ATV_DefReaderCallback_Attribute );
    OTF2_DefReaderCallbacks_SetSystemTreeNodeCallback( def_callbacks, ATV_DefReaderCallback_SystemTreeNode );
    OTF2_DefReaderCallbacks_SetLocationGroupCallback( def_callbacks, ATV_DefReaderCallback_LocationGroup );
    OTF2_DefReaderCallbacks_SetLocationCallback( def_callbacks, ATV_DefReaderCallback_Location );
    OTF2_DefReaderCallbacks_SetRegionCallback( def_callbacks, ATV_DefReaderCallback_Region );
    //OTF2_DefReaderCallbacks_SetCallsiteCallback( def_callbacks, ATV_DefReaderCallback_Callsite );
    //OTF2_DefReaderCallbacks_SetCallpathCallback( def_callbacks, ATV_DefReaderCallback_Callpath );
    //OTF2_DefReaderCallbacks_SetGroupCallback( def_callbacks, ATV_DefReaderCallback_Group );
    //OTF2_DefReaderCallbacks_SetMetricMemberCallback( def_callbacks, ATV_DefReaderCallback_MetricMember );
    //OTF2_DefReaderCallbacks_SetMetricClassCallback( def_callbacks, ATV_DefReaderCallback_MetricClass );
    //OTF2_DefReaderCallbacks_SetMetricInstanceCallback( def_callbacks, ATV_DefReaderCallback_MetricInstance );
    //OTF2_DefReaderCallbacks_SetCommCallback( def_callbacks, ATV_DefReaderCallback_Comm );
    //OTF2_DefReaderCallbacks_SetParameterCallback( def_callbacks, ATV_DefReaderCallback_Parameter );
    //OTF2_DefReaderCallbacks_SetRmaWinCallback( def_callbacks, ATV_DefReaderCallback_RmaWin );
    //OTF2_DefReaderCallbacks_SetMetricClassRecorderCallback( def_callbacks, ATV_DefReaderCallback_MetricClassRecorder );
    //OTF2_DefReaderCallbacks_SetSystemTreeNodePropertyCallback( def_callbacks, ATV_DefReaderCallback_SystemTreeNodeProperty );
    //OTF2_DefReaderCallbacks_SetSystemTreeNodeDomainCallback( def_callbacks, ATV_DefReaderCallback_SystemTreeNodeDomain );
    //OTF2_DefReaderCallbacks_SetLocationGroupPropertyCallback( def_callbacks, ATV_DefReaderCallback_LocationGroupProperty );
    //OTF2_DefReaderCallbacks_SetLocationPropertyCallback( def_callbacks, ATV_DefReaderCallback_LocationProperty );
    //OTF2_DefReaderCallbacks_SetCartDimensionCallback( def_callbacks, ATV_DefReaderCallback_CartDimension );
    //OTF2_DefReaderCallbacks_SetCartTopologyCallback( def_callbacks, ATV_DefReaderCallback_CartTopology );
    //OTF2_DefReaderCallbacks_SetCartCoordinateCallback( def_callbacks, ATV_DefReaderCallback_CartCoordinate );
    //OTF2_DefReaderCallbacks_SetSourceCodeLocationCallback( def_callbacks, ATV_DefReaderCallback_SourceCodeLocation );
    //OTF2_DefReaderCallbacks_SetCallingContextCallback( def_callbacks, ATV_DefReaderCallback_CallingContext );
    //OTF2_DefReaderCallbacks_SetCallingContextPropertyCallback( def_callbacks, ATV_DefReaderCallback_CallingContextProperty );
    //OTF2_DefReaderCallbacks_SetInterruptGeneratorCallback( def_callbacks, ATV_DefReaderCallback_InterruptGenerator );

    return def_callbacks;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */


