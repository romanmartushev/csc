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
