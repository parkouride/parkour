include(${PROJECT_SOURCE_DIR}/src/library/CMakeLists.txt)
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src/simulator)
set (SRC ${LEDVM_COMMON_FILES}
         ${SRC_DIR}/csvfile.cpp
         ${PROJECT_SOURCE_DIR}/src/test.cpp
         )
add_executable(LedVmSimulator ${SRC}) 
include_directories("${PROJECT_SOURCE_DIR}/src/simulator")
add_definitions("-std=c++11")
