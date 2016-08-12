# Copyright (c) 2016 University of Oregon
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIRECTORY})

set(CALLBACK_FILES ATV_DefReaderCallbacks.cpp ATV_EvtReaderCallbacks.cpp ATV_GlobalDefReaderCallbacks.cpp ATV_GlobalEvtReaderCallbacks.cpp callbacks.cpp)
add_library(callbacks OBJECT ${CALLBACK_FILES})

set(READER_FILES trace_reader.cpp trace_data.cpp)
add_library(trace_reader OBJECT ${READER_FILES})

set(GUI_FILES main_window.cpp trace_area.cpp related_list.cpp)
add_library(atv_gui OBJECT ${GUI_FILES})

add_executable (atv main.cpp $<TARGET_OBJECTS:callbacks> $<TARGET_OBJECTS:trace_reader> $<TARGET_OBJECTS:atv_gui>)
target_link_libraries(atv PUBLIC ${LIBS})


INSTALL(TARGETS atv
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

