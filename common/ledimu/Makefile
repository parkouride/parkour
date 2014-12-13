include make/clang.mk

SRC = $(wildcard src/[a-zA-Z]*.cpp)
OBJ = $(subst src/,build/objs/, $(subst .cpp,.o, $(SRC)))

CFLAGS += -DSD_EMU_H -g

all: library test

library: build $(OBJ)
	ar rcs build/ledimu.a $(OBJ)

test: library
	(cd test && make)

build:
	mkdir -p build/objs

build/objs/%.o: src/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build *.gch
