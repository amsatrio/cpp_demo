.PHONY: all build start test clean

all: build

build:
	cmake -B build -S .
	cmake --build build

start: build
	./build/hello_test
	./build/animal_test
	./build/cache_test
	./build/util_generator_test

test: build
	cd build && ctest --output-on-failure

clean:
	rm -rf build

start_cache_api: build
	./build/cache_api