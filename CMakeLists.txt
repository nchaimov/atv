# Copyright (c) 2015-2016 University of Oregon
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW) 
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

project(atv CXX)

include(GitExternal)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    message(INFO " Compiler ${CMAKE_CXX_COMPILER} has C++14 support.")
else()
    CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
    if(COMPILER_SUPPORTS_CXX1Y)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
        message(INFO " Compiler ${CMAKE_CXX_COMPILER} has early C++14 support.")
    else()
        message(FATAL_ERROR " Compiler ${CMAKE_CXX_COMPILER} does not have any C++14 support; please use a newer compiler.")
    endif()
endif()

find_package(Boost 1.54.0 REQUIRED COMPONENTS system thread timer chrono regex)
if(Boost_FOUND)
    message(INFO " Found Boost: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR " Boost 1.54.0 or newer, or a required component, not found.")
endif()

git_external(rapidjson
    https://github.com/miloyip/rapidjson.git
    master
    VERBOSE)

find_path(
    RAPIDJSON_INCLUDE_DIR
    NAMES rapidjson
    PATHS ${PROJECT_SOURCE_DIR}/rapidjson/include)

if(RAPIDJSON_INCLUDE_DIR)
    message(INFO " Found rapidjson at ${RAPIDJSON_INCLUDE_DIR}")
    include_directories(${RAPIDJSON_INCLUDE_DIR})
else()
    message(FATAL_ERROR " rapidjson not found. This should have been checked out automatically. "
        "Try manually checking out https://github.com/miloyip/rapidjson.git to ${PROJECT_SOURCE_DIR}")
endif()

find_package(OTF2)
if(OTF2_FOUND)
    message(INFO " Found OTF2: ${OTF2_INCLUDE_DIRS}")
    include_directories(${OTF2_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${OTF2_LIBRARIES})
else()
    message(FATAL_ERROR " OTF2 not found. Try setting OTF2_ROOT.")
endif()

add_subdirectory(src)

