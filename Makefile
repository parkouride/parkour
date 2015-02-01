all:
	(cd build/ninja && cmake -G Ninja ../..)
	(cd build/xcode && cmake -G Xcode ../..)
