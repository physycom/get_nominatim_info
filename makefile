EXE=get_nominatim_info.exe

all:
	g++ -std=c++11 -I. -o $(EXE) get_nominatim_info.cpp 