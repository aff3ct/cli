# ---------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------------------------- CMAKE PROJECT
# ---------------------------------------------------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.2)
cmake_policy(SET CMP0054 NEW)

project (cli)

# ---------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------------------------- CMAKE OPTIONS
# ---------------------------------------------------------------------------------------------------------------------

option(CLI_COMPILE_STATIC_LIB   "Compile the static library" ON )
option(CLI_COMPILE_SHARED_LIB   "Compile the shared library" OFF)
option(CLI_STATUS_MESSAGE_QUIET "Quiet the status messages"  OFF)

# ---------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------------------- CMAKE CONFIGURATION
# ---------------------------------------------------------------------------------------------------------------------

# set CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR and CMAKE_INSTALL_DATAROOTDIR variables
include(GNUInstallDirs)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify lib path
set(LIBRARY_OUTPUT_PATH lib/)

# Generate the source files lists
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

# ---------------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------- OBJECTS/LIBS/EXE
# ---------------------------------------------------------------------------------------------------------------------

# Object
add_library(cli-obj OBJECT ${SRC_FILES})
set_target_properties(cli-obj PROPERTIES
                              POSITION_INDEPENDENT_CODE ON) # set -fpic

# Shared library
if(CLI_COMPILE_SHARED_LIB)
    add_library(cli-shared-lib SHARED $<TARGET_OBJECTS:cli-obj>)
    set_target_properties(cli-shared-lib PROPERTIES
                                         OUTPUT_NAME cli
                                         POSITION_INDEPENDENT_CODE ON) # set -fpic
    if(NOT CLI_STATUS_MESSAGE_QUIET)
        message(STATUS "cli - Compile: shared library")
    endif()
endif(CLI_COMPILE_SHARED_LIB)

# Static library
if(CLI_COMPILE_STATIC_LIB)
    add_library(cli-static-lib STATIC $<TARGET_OBJECTS:cli-obj>)
    set_target_properties(cli-static-lib PROPERTIES
                                         OUTPUT_NAME cli
                                         POSITION_INDEPENDENT_CODE ON) # set -fpic
    if(NOT CLI_STATUS_MESSAGE_QUIET)
        message(STATUS "cli - Compile: static library")
    endif()
endif(CLI_COMPILE_STATIC_LIB)

# ---------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------- HEADER ONLY LIBRARIES
# ---------------------------------------------------------------------------------------------------------------------

# cli
target_include_directories(cli-obj PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/cli/>)
if(CLI_COMPILE_SHARED_LIB)
    target_include_directories(cli-shared-lib PRIVATE
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/>
                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/cli/>)
endif(CLI_COMPILE_SHARED_LIB)
if(CLI_COMPILE_STATIC_LIB)
    target_include_directories(cli-static-lib PRIVATE
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/>
                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/cli/>)
endif(CLI_COMPILE_STATIC_LIB)

# rang
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/rang/include/rang.hpp")
    target_include_directories(cli-obj PRIVATE
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/rang/include/>)
else()
    message(FATAL_ERROR "cli - rang can't be found, try to init the submodule with the following cmd:\n"
                        "$ git submodule update --init --recursive")
endif()

# ---------------------------------------------------------------------------------------------------------------------
# -------------------------------------------------------------------------------------------------------------- EXPORT
# ---------------------------------------------------------------------------------------------------------------------

if (CLI_COMPILE_SHARED_LIB AND NOT CLI_COMPILE_STATIC_LIB)
    export(TARGETS
           cli-shared-lib
           NAMESPACE cli::
           FILE "lib/cmake/cli/cli-config.cmake")
endif()

if (CLI_COMPILE_STATIC_LIB AND NOT CLI_COMPILE_SHARED_LIB)
    export(TARGETS
           cli-static-lib
           NAMESPACE cli::
           FILE "lib/cmake/cli/cli-config.cmake")
endif()

if(CLI_COMPILE_SHARED_LIB AND CLI_COMPILE_STATIC_LIB)
    export(TARGETS
           cli-shared-lib
           cli-static-lib
           NAMESPACE cli::
           FILE "lib/cmake/cli/cli-config.cmake")
endif()

# ---------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------------------------------- INSTALL
# ---------------------------------------------------------------------------------------------------------------------

if(CLI_COMPILE_SHARED_LIB)
    if(WIN32)
        install(TARGETS cli-shared-lib
                EXPORT cli-config
                RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}/
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/
                COMPONENT library)
    else()
        install(TARGETS cli-shared-lib
                EXPORT cli-config
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/
                COMPONENT library)
    endif()
endif()
if(CLI_COMPILE_STATIC_LIB)
    install(TARGETS cli-static-lib
            EXPORT cli-config
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/
            COMPONENT library)
endif()

if (CLI_COMPILE_SHARED_LIB OR CLI_COMPILE_STATIC_LIB)
    install(EXPORT
            cli-config
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cli/"
            NAMESPACE cli::
            COMPONENT library)

    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cli
            COMPONENT headers
            FILES_MATCHING PATTERN "*.h")
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cli
            COMPONENT headers
            FILES_MATCHING PATTERN "*.hpp")
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cli
            COMPONENT headers
            FILES_MATCHING PATTERN "*.hxx")
endif()