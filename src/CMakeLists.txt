# Copyright (c) 2016 University of Oregon
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIRECTORY})

set(CALLBACK_FILES ATV_DefReaderCallbacks.cpp ATV_EvtReaderCallbacks.cpp ATV_GlobalDefReaderCallbacks.cpp ATV_GlobalEvtReaderCallbacks.cpp callbacks.cpp)
add_library(callbacks OBJECT ${CALLBACK_FILES})

set(READER_FILES files.cpp trace_reader.cpp trace_data.cpp)
add_library(trace_reader OBJECT ${READER_FILES})

set(GUI_FILES main_window.cpp trace_area.cpp related_list.cpp idle_list.cpp)
add_library(atv_gui OBJECT ${GUI_FILES})        

set(ANALYSIS_FILES idle_detector.cpp)
add_library(analysis OBJECT ${ANALYSIS_FILES})

add_executable (atv main.cpp $<TARGET_OBJECTS:callbacks> $<TARGET_OBJECTS:trace_reader> $<TARGET_OBJECTS:atv_gui> $<TARGET_OBJECTS:analysis> )
target_link_libraries(atv ${LIBS})

add_executable (atv_analyze main_analyze.cpp $<TARGET_OBJECTS:analysis> $<TARGET_OBJECTS:callbacks> $<TARGET_OBJECTS:trace_reader>)
target_link_libraries(atv_analyze ${LIBS})

INSTALL(TARGETS atv atv_analyze
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

