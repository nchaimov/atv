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

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

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

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -flto -O3 -ffast-math")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -flto -O3 -ffast-math")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -march=native -flto -O3 -ffast-math")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -march=native -flto -O3 -ffast-math")

IF (CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
  # Use the highest warning level for visual studio.
  SET(CMAKE_CXX_WARNING_LEVEL 4)
  IF (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    STRING(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  ELSE (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  ENDIF (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")

  SET(CMAKE_C_WARNING_LEVEL 4)
  IF (CMAKE_C_FLAGS MATCHES "/W[0-4]")
    STRING(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  ELSE (CMAKE_C_FLAGS MATCHES "/W[0-4]")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
  ENDIF (CMAKE_C_FLAGS MATCHES "/W[0-4]")

ELSEIF (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC)
  # use -Wall for gcc
  IF(NOT CMAKE_CXX_FLAGS MATCHES "-Wall$")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  ENDIF(NOT CMAKE_CXX_FLAGS MATCHES "-Wall$")

  IF(NOT CMAKE_C_FLAGS MATCHES "-Wall$")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  ENDIF(NOT CMAKE_C_FLAGS MATCHES "-Wall$")

ELSE (CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
  MESSAGE(STATUS "Unknown build tool, cannot set warning flags for your")
ENDIF (CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")

find_package(Boost 1.54.0 REQUIRED COMPONENTS system thread timer chrono regex program_options filesystem)
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

find_program(OTF2_TEMPLATE
    NAMES otf2-template
    HINTS ${OTF2_ROOT} ${OTF2_ROOT}/bin ${OTF2_INCLUDE_DIRS}/../bin)
if(OTF2_TEMPLATE)
    message(INFO " found otf2-template: ${OTF2_TEMPLATE}")
else()
    message(FATAL_ERROR " could not find otf2-template; please add it to your PATH")
endif()

    
find_package(PkgConfig REQUIRED)
# Use the package PkgConfig to detect GTKmm headers/library files
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTKMM_CFLAGS_OTHER})
set(LIBS ${LIBS} ${GTKMM_LIBRARIES})

# Use the package PkgConfig to detect CairoMM headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${CAIROMM_INCLUDE_DIRS})
link_directories(${CAIROMM_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${CAIROMM_CFLAGS_OTHER})
set(LIBS ${LIBS} ${CAIROMM_LIBRARIES})

if(USE_JEMALLOC)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JEMALLOC REQUIRED jemalloc)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${JEMALLOC_INCLUDE_DIRS})
link_directories(${JEMALLOC_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${JEMALLOC_CFLAGS_OTHER})
set(LIBS ${LIBS} ${JEMALLOC_LIBRARIES})
endif()

add_subdirectory(templates)
add_subdirectory(src)

