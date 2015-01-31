cmake_minimum_required (VERSION 2.6)
project (ledvm)

set (ledvm_VERSION_MAJOR 0)
set (ledvm_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/Version.h.in"
    "${PROJECT_BINARY_DIR}/gen/Version.h"
)

include_directories("${PROJECT_BINARY_DIR}/gen")
