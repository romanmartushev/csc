#ifndef SYMBOL
#define SYMBOL

#include <string>

enum Type { Scribble, Int, Float };

using namespace std;

class Symbol
{
public:
	string Name;
	Type DataType;
	int RelativeAddress;
	bool ArrayIndicator;
	int NumberOfComponents;
	float InitialValue;

	string stringValue;

	Symbol(string Name, Type DataType);
	Symbol(string Name);
	Symbol();
};
#endif
