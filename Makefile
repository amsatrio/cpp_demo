.SILENT: build
.SILENT: start
build:
	g++ main.cpp -o bin/cpp_demo
start: build
	bin/cpp_demo
clean:
	rm -rf bin/*
