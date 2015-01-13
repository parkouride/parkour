THIS_MAKEFILE_PATH:=$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
THIS_DIR:=$(shell cd $(dir $(THIS_MAKEFILE_PATH));pwd)
PROJECT_DIR = $(THIS_DIR)
USER_LIB_PATH := $(PROJECT_DIR)/lib
CFLAGS_STD = -std=gnu11
CXXFLAGS_STD = -std=gnu++11
CXXFLAGS = -pedantic -Wall -Wextra
CXXFLAGS += -fdiagnostics-color
CXXFLAGS += -I$(USER_LIB_PATH)/ledimuff

ARDUINO_DIR = /Applications/ArduinoYun.app/Contents/Resources/Java
ARDMK_DIR = /usr/local/Cellar/arduino-mk/HEAD
AVR_TOOLS_DIR = /usr/local
MONITOR_PORT = /dev/ttyACM0
BOARD_TAG = pro
BOARD_SUB = 16MHzatmega328
ARCHITECTURE = avr
ARDUINO_LIBS = 

CURRENT_DIR = $(shell basename $(CURDIR))
OBJDIR = $(PROJECT_DIR)/build/$(BOARD_TAG)/$(CURRENT_DIR)

include /usr/local/opt/arduino-mk/Arduino.mk
