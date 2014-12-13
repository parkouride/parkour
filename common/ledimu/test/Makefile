include ../make/clang.mk

GTEST_ROOT = ../../gtest-1.7.0
BUILD_DIR = ../build
OBJ_DIR = $(BUILD_DIR)/objs

SRC = $(wildcard ./ledimuff/*.cpp) ./main.cpp
OBJ = $(subst ./,$(OBJ_DIR)/, $(subst .cpp,.o, $(SRC)))
PRODUCT_OBJ = $(BUILD_DIR)/ledimu.a

CFLAGS += -I $(GTEST_ROOT) -I $(GTEST_ROOT)/include -I ../src

all: build run

build: gtest tests
	@echo "Building Tests"

gtest: $(GTEST_ROOT)/src/gtest-all.cc
	$(CC) $(CFLAGS) -pthread -c $(GTEST_ROOT)/src/gtest-all.cc -o $(OBJ_DIR)/gtest-all.o
	ar -rv $(BUILD_DIR)/libgtest.a $(OBJ_DIR)/gtest-all.o

tests: $(OBJ)
	$(CC) -o $(BUILD_DIR)/tests $(BUILD_DIR)/libgtest.a $(OBJ) $(PRODUCT_OBJ)

$(OBJ_DIR)/%.o: ./%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

run: tests
	$(BUILD_DIR)/tests --gtest_shuffle
