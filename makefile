CXX = g++
CC = g++
FLAGS = -std=c++11

all:   csc

csc: csc.cpp cscScan.o
	$(CXX) $(FLAGS) cscScan.o csc.cpp -o csc

cscScan.o: cscScan.cpp
	$(CXX) $(FLAGS) -c cscScan.cpp

clobber:
	rm -f *.o *.exe *.lis *.obj core csc sam macc trace.txt
