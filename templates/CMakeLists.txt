
set(ATV_GENERATE_TARGETS ATV_GlobalDefReaderCallbacks.h ATV_GlobalDefReaderCallbacks.cpp ATV_DefReaderCallbacks.h ATV_DefReaderCallbacks.cpp ATV_GlobalEvtReaderCallbacks.h ATV_GlobalEvtReaderCallbacks.cpp ATV_EvtReaderCallbacks.h ATV_EvtReaderCallbacks.cpp)

foreach(targetName ${ATV_GENERATE_TARGETS})
    add_custom_command(
        OUTPUT ${targetName}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${targetName}.tmpl ${targetName}.tmpl
        COMMAND ${OTF2_TEMPLATE} ${targetName}.tmpl ${targetName}
        DEPENDS ${targetName}.tmpl)
endforeach()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(generate
    DEPENDS ${ATV_GENERATE_TARGETS})

