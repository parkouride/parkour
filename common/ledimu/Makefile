all: library test

SRC = src/ledimuff.cpp

OBJ = $(subst src/,build/objs/, $(subst .cpp,.o, $(SRC)))

library: build $(OBJ)
	ar rcs build/ledimu.a $(OBJ)

test: library
	(cd test && make)

build:
	mkdir -p build/objs

build/objs/%.o: src/%.cpp src/%.h 
	clang++ -c -DSD_EMU_H -std=c++11 -stdlib=libstdc++ $< -o $@

clean:
	rm -rf build *.gch
