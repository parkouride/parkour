GTEST_ROOT = /home/rhay/d/gtest-1.7.0
BUILD_DIR = ../build/objs

SRC = ./main.cpp

OBJ = $(subst ./,$(BUILD_DIR)/, $(subst .cpp,.o, $(SRC)))

all: build run

build: gtest tests
	@echo "Building Tests"

gtest:
	clang++ -std=c++11 -I ${GTEST_ROOT} -I ${GTEST_ROOT}/include -pthread -c ${GTEST_ROOT}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

tests: $(OBJ)

$(BUILD_DIR)/%.o: %.cpp
	@touch $@

run:
	@echo "Running Tests"
