# Copyright (c) 2016 University of Oregon
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CMAKE_CURRENT_SOURCE_DIRECTORY})

set(CALLBACK_FILES ATV_DefReaderCallbacks.cpp ATV_EvtReaderCallbacks.cpp ATV_GlobalDefReaderCallbacks.cpp ATV_GlobalEvtReaderCallbacks.cpp)
add_library(callbacks OBJECT ${CALLBACK_FILES})

add_executable (test_trace_read test_trace_read.cpp $<TARGET_OBJECTS:callbacks>)
target_link_libraries(test_trace_read PUBLIC ${LIBS})


INSTALL(TARGETS test_trace_read
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

