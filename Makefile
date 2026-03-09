.PHONY: all build start test clean

all: build

build:
	cmake -B build -S .
	cmake --build build

start: build
	./build/unit_tests
	./build/animal_test

test: build
	cd build && ctest --output-on-failure

clean:
	rm -rf build