CXX = g++
CC = g++
FLAGS = 

all:    macc sam

sam: sam2018.cpp
	$(CXX) $(FLAGS) sam2018.cpp -o sam

macc: macc2018.cpp
	$(CXX) $(FLAGS) macc2018.cpp -o macc

clobber:
	rm -f *.o *.exe *.lis *.obj core sam macc trace.txt

