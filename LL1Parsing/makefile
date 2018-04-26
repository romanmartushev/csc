CXX = g++
CC = g++
FLAGS = 

all:    llgen parsergen

llgen: llgen2018.cpp Intset.h
	$(CXX) $(FLAGS) llgen2018.cpp -o llgen

parsergen: parserGen2018.cpp
	$(CXX) $(FLAGS) parserGen2018.cpp -o parsergen

clobber:
	rm -f *.o *.exe *.lis *.obj core llgen parsergen trace.txt

