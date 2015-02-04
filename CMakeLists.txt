cmake_minimum_required (VERSION 2.8)
project (ledide)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist)
FIND_PACKAGE(Qt4 REQUIRED)
include(UseQt4)
include(DeployQt4)

set (ledvm_VERSION_MAJOR 0)
set (ledvm_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/Version.h.in"
    "${PROJECT_BINARY_DIR}/gen/Version.h"
)

include_directories("${PROJECT_BINARY_DIR}/gen")
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS("-std=c++11")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/widgets")
