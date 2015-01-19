set (ARDUINO_DIR ${PROJECT_SOURCE_DIR}/src/arduino)

add_custom_target(BuildArduino ALL
    COMMAND make
    WORKING_DIRECTORY ${ARDUINO_DIR}
    COMMENT Build the Arduino elf file
    SOURCES ${ARDUINO_DIR}/src/test.cpp
)

add_custom_target(upload
    COMMAND make upload
    WORKING_DIRECTORY ${ARDUINO_DIR}
    COMMENT Build the Arduino elf file
    DEPENDS BuildArduino
)
