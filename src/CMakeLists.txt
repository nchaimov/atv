# Copyright (c) 2016 University of Oregon
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


add_executable (test_trace_read test_trace_read.cpp)
target_link_libraries(test_trace_read PUBLIC ${LIBS})

INSTALL(TARGETS test_trace_read
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

