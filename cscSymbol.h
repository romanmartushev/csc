#ifndef SYMBOL
#define SYMBOL

#include <string>
#include <vector>

enum Type { Scribble, Int, Float, Float_Array, Int_Array };

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
	vector <float> ArrayValues;
	string stringValue;
	Symbol(string Name, Type DataType);
	Symbol(string Name);
	Symbol();
};
#endif
