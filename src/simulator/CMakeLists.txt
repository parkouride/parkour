include(${PROJECT_SOURCE_DIR}/src/library/CMakeLists.txt)
set (SRC ${LEDVM_COMMON_FILES}
         ${PROJECT_SOURCE_DIR}/src/test.cpp
         )
add_executable(LedVmSimulator ${SRC}) 
include_directories("${PROJECT_SOURCE_DIR}/src/simulator")
add_definitions("-std=c++11")
