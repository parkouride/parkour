include ../make/clang.mk

GTEST_ROOT = ../../gtest-1.7.0
BUILD_DIR = ../build
OBJ_DIR = $(BUILD_DIR)/objs

SRC = ./main.cpp
OBJ = $(subst ./,$(OBJ_DIR)/, $(subst .cpp,.o, $(SRC)))

CFLAGS += -I $(GTEST_ROOT) -I $(GTEST_ROOT)/include

all: build run

build: gtest tests
	@echo "Building Tests"

gtest: $(GTEST_ROOT)/src/gtest-all.cc
	$(CC) $(CFLAGS) -pthread -c $(GTEST_ROOT)/src/gtest-all.cc -o $(OBJ_DIR)/gtest-all.o
	ar -rv $(BUILD_DIR)/libgtest.a $(OBJ_DIR)/gtest-all.o

tests: $(OBJ)
	$(CC) -o $(BUILD_DIR)/tests $(BUILD_DIR)/libgtest.a $(OBJ)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: tests
	$(BUILD_DIR)/tests
