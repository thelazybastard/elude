.PHONY: build run clean

build:
	@cmake -B build -G Ninja

run:
	@cmake --build build && ./build/elude

clean:
	@rm -rf build