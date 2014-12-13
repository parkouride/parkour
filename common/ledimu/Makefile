include make/clang.mk

SRC = src/ledimuff.cpp
OBJ = $(subst src/,build/objs/, $(subst .cpp,.o, $(SRC)))

CFLAGS += -DSD_EMU_H

all: library test

library: build $(OBJ)
	ar rcs build/ledimu.a $(OBJ)

test: library
	(cd test && make)

build:
	mkdir -p build/objs

build/objs/%.o: src/%.cpp src/%.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build *.gch
