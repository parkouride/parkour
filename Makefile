all: build_files

build_files:
	(mkdir -p build/ninja; cd build/ninja && cmake -G Ninja ../..)
	(mkdir -p build/xcode; cd build/xcode && cmake -G Xcode ../..)

ninja: build_files
	(cd build/ninja && ninja)

clean:
	rm -rf build
