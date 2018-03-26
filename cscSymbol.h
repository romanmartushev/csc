#ifndef SYMBOL
#define SYMBOL

#include <string>

enum Type { Scribble, Int, Float };

using namespace std;

class Symbol
{
public:
	//static int Offset;
	string Name;
	Type DataType;
	int RelativeAddress;
	bool ArrayIndicator;
	int NumberOfComponents;
	float InitialValue;

	Symbol(string Name, Type DataType);
	Symbol(string Name);
	Symbol();

	//void SetupRelativeAddress();
};

//int Symbol::Offset = 0;
#endif