
#include "ATV_GlobalDefReaderCallbacks.h"

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OTF2_CallbackCode ATV_GlobalDefReaderCallback_Unknown( void * userData ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_ClockProperties ( void* userData ,
uint64_t timerResolution,
uint64_t globalOffset,
uint64_t traceLength ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Paradigm ( void* userData ,
OTF2_Paradigm paradigm,
OTF2_StringRef name,
OTF2_ParadigmClass paradigmClass ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_ParadigmProperty ( void* userData ,
OTF2_Paradigm paradigm,
OTF2_ParadigmProperty property,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_String ( void* userData ,
OTF2_StringRef self,
const char* string ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Attribute ( void* userData ,
OTF2_AttributeRef self,
OTF2_StringRef name,
OTF2_StringRef description,
OTF2_Type type ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_SystemTreeNode ( void* userData ,
OTF2_SystemTreeNodeRef self,
OTF2_StringRef name,
OTF2_StringRef className,
OTF2_SystemTreeNodeRef parent ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_LocationGroup ( void* userData ,
OTF2_LocationGroupRef self,
OTF2_StringRef name,
OTF2_LocationGroupType locationGroupType,
OTF2_SystemTreeNodeRef systemTreeParent ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Location ( void* userData ,
OTF2_LocationRef self,
OTF2_StringRef name,
OTF2_LocationType locationType,
uint64_t numberOfEvents,
OTF2_LocationGroupRef locationGroup ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Region ( void* userData ,
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
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Callsite ( void* userData ,
OTF2_CallsiteRef self,
OTF2_StringRef sourceFile,
uint32_t lineNumber,
OTF2_RegionRef enteredRegion,
OTF2_RegionRef leftRegion ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Callpath ( void* userData ,
OTF2_CallpathRef self,
OTF2_CallpathRef parent,
OTF2_RegionRef region ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Group ( void* userData ,
OTF2_GroupRef self,
OTF2_StringRef name,
OTF2_GroupType groupType,
OTF2_Paradigm paradigm,
OTF2_GroupFlag groupFlags,
uint32_t numberOfMembers,
const uint64_t* members ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_MetricMember ( void* userData ,
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


OTF2_CallbackCode ATV_GlobalDefReaderCallback_MetricClass ( void* userData ,
OTF2_MetricRef self,
uint8_t numberOfMetrics,
const OTF2_MetricMemberRef* metricMembers,
OTF2_MetricOccurrence metricOccurrence,
OTF2_RecorderKind recorderKind ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_MetricInstance ( void* userData ,
OTF2_MetricRef self,
OTF2_MetricRef metricClass,
OTF2_LocationRef recorder,
OTF2_MetricScope metricScope,
uint64_t scope ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Comm ( void* userData ,
OTF2_CommRef self,
OTF2_StringRef name,
OTF2_GroupRef group,
OTF2_CommRef parent ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_Parameter ( void* userData ,
OTF2_ParameterRef self,
OTF2_StringRef name,
OTF2_ParameterType parameterType ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_RmaWin ( void* userData ,
OTF2_RmaWinRef self,
OTF2_StringRef name,
OTF2_CommRef comm ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_MetricClassRecorder ( void* userData ,
OTF2_MetricRef metricClass,
OTF2_LocationRef recorder ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_SystemTreeNodeProperty ( void* userData ,
OTF2_SystemTreeNodeRef systemTreeNode,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_SystemTreeNodeDomain ( void* userData ,
OTF2_SystemTreeNodeRef systemTreeNode,
OTF2_SystemTreeDomain systemTreeDomain ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_LocationGroupProperty ( void* userData ,
OTF2_LocationGroupRef locationGroup,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_LocationProperty ( void* userData ,
OTF2_LocationRef location,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_CartDimension ( void* userData ,
OTF2_CartDimensionRef self,
OTF2_StringRef name,
uint32_t size,
OTF2_CartPeriodicity cartPeriodicity ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_CartTopology ( void* userData ,
OTF2_CartTopologyRef self,
OTF2_StringRef name,
OTF2_CommRef communicator,
uint8_t numberOfDimensions,
const OTF2_CartDimensionRef* cartDimensions ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_CartCoordinate ( void* userData ,
OTF2_CartTopologyRef cartTopology,
uint32_t rank,
uint8_t numberOfDimensions,
const uint32_t* coordinates ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_SourceCodeLocation ( void* userData ,
OTF2_SourceCodeLocationRef self,
OTF2_StringRef file,
uint32_t lineNumber ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_CallingContext ( void* userData ,
OTF2_CallingContextRef self,
OTF2_RegionRef region,
OTF2_SourceCodeLocationRef sourceCodeLocation,
OTF2_CallingContextRef parent ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_CallingContextProperty ( void* userData ,
OTF2_CallingContextRef callingContext,
OTF2_StringRef name,
OTF2_Type type,
OTF2_AttributeValue value ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_CallbackCode ATV_GlobalDefReaderCallback_InterruptGenerator ( void* userData ,
OTF2_InterruptGeneratorRef self,
OTF2_StringRef name,
OTF2_InterruptGeneratorMode interruptGeneratorMode,
OTF2_Base base,
int64_t exponent,
uint64_t period ) {
    return OTF2_CALLBACK_SUCCESS;
}


OTF2_GlobalDefReaderCallbacks * ATV_CreateGlobalDefReaderCallbacks(void) {
    OTF2_GlobalDefReaderCallbacks * global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();
    OTF2_GlobalDefReaderCallbacks_SetUnknownCallback(global_def_callbacks, ATV_GlobalDefReaderCallback_Unknown);
    OTF2_GlobalDefReaderCallbacks_SetClockPropertiesCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_ClockProperties );
    OTF2_GlobalDefReaderCallbacks_SetParadigmCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Paradigm );
    OTF2_GlobalDefReaderCallbacks_SetParadigmPropertyCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_ParadigmProperty );
    OTF2_GlobalDefReaderCallbacks_SetStringCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_String );
    OTF2_GlobalDefReaderCallbacks_SetAttributeCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Attribute );
    OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodeCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_SystemTreeNode );
    OTF2_GlobalDefReaderCallbacks_SetLocationGroupCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_LocationGroup );
    OTF2_GlobalDefReaderCallbacks_SetLocationCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Location );
    OTF2_GlobalDefReaderCallbacks_SetRegionCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Region );
    OTF2_GlobalDefReaderCallbacks_SetCallsiteCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Callsite );
    OTF2_GlobalDefReaderCallbacks_SetCallpathCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Callpath );
    OTF2_GlobalDefReaderCallbacks_SetGroupCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Group );
    OTF2_GlobalDefReaderCallbacks_SetMetricMemberCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_MetricMember );
    OTF2_GlobalDefReaderCallbacks_SetMetricClassCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_MetricClass );
    OTF2_GlobalDefReaderCallbacks_SetMetricInstanceCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_MetricInstance );
    OTF2_GlobalDefReaderCallbacks_SetCommCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Comm );
    OTF2_GlobalDefReaderCallbacks_SetParameterCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_Parameter );
    OTF2_GlobalDefReaderCallbacks_SetRmaWinCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_RmaWin );
    OTF2_GlobalDefReaderCallbacks_SetMetricClassRecorderCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_MetricClassRecorder );
    OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodePropertyCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_SystemTreeNodeProperty );
    OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodeDomainCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_SystemTreeNodeDomain );
    OTF2_GlobalDefReaderCallbacks_SetLocationGroupPropertyCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_LocationGroupProperty );
    OTF2_GlobalDefReaderCallbacks_SetLocationPropertyCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_LocationProperty );
    OTF2_GlobalDefReaderCallbacks_SetCartDimensionCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_CartDimension );
    OTF2_GlobalDefReaderCallbacks_SetCartTopologyCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_CartTopology );
    OTF2_GlobalDefReaderCallbacks_SetCartCoordinateCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_CartCoordinate );
    OTF2_GlobalDefReaderCallbacks_SetSourceCodeLocationCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_SourceCodeLocation );
    OTF2_GlobalDefReaderCallbacks_SetCallingContextCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_CallingContext );
    OTF2_GlobalDefReaderCallbacks_SetCallingContextPropertyCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_CallingContextProperty );
    OTF2_GlobalDefReaderCallbacks_SetInterruptGeneratorCallback( global_def_callbacks, ATV_GlobalDefReaderCallback_InterruptGenerator );

    return global_def_callbacks;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

