#include "cscSymbol.h"

Symbol::Symbol(string name, Type dataType)
{
	Name = name;
	DataType = dataType;
}

Symbol::Symbol(string name)
{
	Name = name;
}

Symbol::Symbol()
{

}

/*void Symbol::SetupRelativeAddress()
{
	int size;

	switch(DataType)
	{
		case Int:
			size = 1;
			break;
		case Float:
			size = 2;
			break;
		case Scribble:

			break;
			//Todo
	}

	RelativeAddress = this->Offset + size;
	this->Offset += size;
}*/