EXE=get_nominatim_info.exe

all: dirtree
	$(CXX) -std=c++11 -Isrc/jsoncons/src -o bin/$(EXE) src/get_nominatim_info.cpp 

dirtree:
	@mkdir -p bin

