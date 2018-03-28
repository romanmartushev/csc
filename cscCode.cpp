/*	____________________________________________________________________________

	    Semantics and Coding Component Implementation for the :Scopy Compiler
	____________________________________________________________________________
*/

#include <iostream>
#include <fstream>
using namespace std;

extern ifstream sourceFile;
extern ofstream outFile, listFile;

#include "cscScan.h"   // Scanner class definition
#include "cscCode.h"   // CodeGen class definition


extern Scanner scan; // global Scanner object declared in micro.cpp

// *******************
// **  Constructor  **
// *******************

CodeGen::CodeGen()
{
	maxTemp = 0;
}

// *******************************
// ** Private Member Functions  **
// *******************************

void CodeGen::CheckId(const ExprRec & s)
{
	if (!LookUp(s.name))  // variable not declared yet
		Enter(s);
}

void CodeGen::Enter(const ExprRec & s)
{
	Symbol symbol;
	int size;
	switch(s.kind)
	{
		case ID_EXPR:
		case LITERAL_EXPR:
		case TEMP_EXPR:
		case INT_LITERAL_EXPR:
			symbol.DataType = Int;
			symbol.InitialValue = s.val;
			size = 2;
		break;
		case FLOAT_LITERAL_EXPR:
			symbol.DataType = Float;
			symbol.InitialValue = s.val;
			size = 4;
		break;
		case SCRIBBLE_LITERAL_EXPR:
			symbol.DataType = Scribble;
			//TODO: Size
		break;
	}
	symbol.Name = s.name;
	symbol.RelativeAddress = Offset;

	Offset += size;
	Offset = Offset % 2 == 1 ? Offset += 1 : Offset;

	symbolTable.push_back(symbol);
}

string CodeGen::ExtractOp(const OpRec & o)
{
	if(o.kind == INT_LITERAL_EXPR){
		switch(o.op)
		{
			case PLUS:
				return "IA        ";
			case MINUS:
				return "IS        ";
			case MULTIPLY:
				return "IM        ";
			case DIVIDE:
				return "ID        ";
		}
	}else if (o.kind == FLOAT_LITERAL_EXPR){
		switch(o.op)
		{
			case PLUS:
				return "FA        ";
			case MINUS:
				return "FS        ";
			case MULTIPLY:
				return "FM        ";
			case DIVIDE:
				return "FD        ";
		}
	}else{
			string s = "There was an issue with code.ExtractOp()";
			cout << s << endl;
			return s;
	}
}

void CodeGen::Generate(const string & s1, const string & s2, const string & s3)
{
	listFile.width(20);
	listFile << ' ' << s1;
	outFile << s1;
	if (s2.length() > 0)
	{
		listFile << s2;
		outFile << s2;
		if (s3.length() > 0)
		{
			listFile << ',' << s3;
			outFile << ',' << s3;
		}
	}
	listFile << endl;
	outFile << endl;
}

string CodeGen::GetTemp()
{
	string s;
	static string t;

	t = "Temp&";
	IntToAlpha(++maxTemp, s);
	t += s;
	return t;
}

void CodeGen::IntToAlpha(int val, string& str)
{
	int k;
	char temp;

	str = "";
	if (val == 0) str = "0";
	while (val > 0)
	{
		str.append(1, (char)(val % 10 + (int)'0'));
		val /= 10;
	}
	k = int(str.length());
	for (int i = 0; i < k/2; i++)
	{
		temp = str[i];
		str[i] = str[k-i-1];
		str[k-i-1] = temp;
	}
}

bool CodeGen::LookUp(const string & s)
{
	for (unsigned i = 0; i < symbolTable.size(); i++)
	if (symbolTable[i].Name == s)
		return true;

	return false;
}

// ******************************
// ** Public Member Functions  **
// ******************************

void CodeGen::Assign(ExprRec & target, ExprRec & source)
{
	string s;
	GetSymbolValue(source,s);
	Generate("LD        ", "R0", s);
	GetSymbolValue(target,s);
	Generate("STO       ", "R0", s);
}

void CodeGen::Finish()
{
	string s;

	listFile.width(6);
	listFile << ++scan.lineNumber << "  " << scan.lineBuffer << endl;
	Generate("HALT      ", "", "");
	Generate("LABEL     ", "VARS", "");
	IntToAlpha(int(2*(symbolTable.size()+1)), s);
	Generate("SKIP      ", s, "");
	outFile.close();
	listFile << endl << endl;
	listFile << " _____________________________________________\n";
	listFile << " <><><><>   S Y M B O L   T A B L E   <><><><>\n"
		<< endl;
	listFile << " Relative" << endl;
	listFile << " Address      Identifier      Value      Type" << endl;
	listFile << " --------     ----------      -----      -----"
		<< endl;
	for (unsigned i = 0; i < symbolTable.size(); i++)
	{
		listFile.width(7);
		listFile << symbolTable[i].RelativeAddress << "       "<< symbolTable[i].Name << "               "
		<< symbolTable[i].InitialValue << "          " << symbolTable[i].DataType << endl;
	}
	listFile << " _____________________________________________"
		<< endl;
	listFile << endl;
	listFile << " Normal successful compilation." << endl;
	listFile.close();
}

void CodeGen::GenInfix(ExprRec & e1, const OpRec & op, ExprRec & e2, ExprRec& e)
{
	string opnd;
	if (e1.kind == LITERAL_EXPR && e2.kind == LITERAL_EXPR)
	{
		e.kind = LITERAL_EXPR;
		switch (op.op)
		{
		case PLUS:
			e.val = e1.val + e2.val;
			break;
		case MINUS:
			e.val = e1.val - e2.val;
			break;
		case MULTIPLY:
			e.val = e1.val * e2.val;
			break;
		case DIVIDE:
			e.val = e1.val/e2.val;
			break;
		}
	}
	else
	{
		e.name = GetTemp();
		CheckId(e);

		GetSymbolValue(e1,opnd);
		Generate("LD        ", "R0", opnd);
		GetSymbolValue(e2,opnd);
		Generate(ExtractOp(op), "R0", opnd);
		GetSymbolValue(e,opnd);
		Generate("STO       ", "R0", opnd);
	}
}

void CodeGen::NewLine()
{
	Generate("WRNL      ", "", "");
}

void CodeGen::ProcessVar(ExprRec& e)
{
	string s;
	//e.name = scan.tokenBuffer;
	GetSymbolValue(e, s);
}

void CodeGen::ProcessLit(ExprRec& e)
{
	e.kind = LITERAL_EXPR;

	if(scan.tokenBuffer.find(".") < scan.tokenBuffer.length()
		|| scan.tokenBuffer.find("e") < scan.tokenBuffer.length()
		|| scan.tokenBuffer.find("E") < scan.tokenBuffer.length())
	{
		e.name = "float";
		e.val = atof(scan.tokenBuffer.data());
	}
	else
	{
		e.name = "int";
		e.val = atoi(scan.tokenBuffer.data());
	}
}

void CodeGen::ProcessOp(OpRec& o)
{
	if (scan.tokenBuffer == "+")
		o.op = PLUS;
	else if (scan.tokenBuffer == "-")
		o.op = MINUS;
	else if (scan.tokenBuffer == "*")
		o.op = MULTIPLY;
	else if (scan.tokenBuffer == "/")
		o.op = DIVIDE;
}

void CodeGen::InputVar(ExprRec & inVar)
{
	string s;
	GetSymbolValue(inVar,s);
	if(inVar.kind == INT_LITERAL_EXPR)
		Generate("RDI       ", s, "");
	if(inVar.kind == FLOAT_LITERAL_EXPR)
		Generate("RDF       ", s, "");
}

void CodeGen::Start()
{
	Generate("LDA       ", "R15", "VARS");
}

void CodeGen::WriteExpr(ExprRec & outExpr)
{
	string s;
	GetSymbolValue(outExpr,s);
	if(outExpr.kind == INT_LITERAL_EXPR || outExpr.name == "int")
		Generate("WRI       ", s, "");
	if(outExpr.kind == FLOAT_LITERAL_EXPR || outExpr.name == "float")
		Generate("WRF       ", s, "");
}

void CodeGen::GetSymbolValue(ExprRec& e, string & s)
{
	int index;
	string t;

	if(e.kind == LITERAL_EXPR){
		IntToAlpha(e.val, t);
		s = "#" + t;
	}
	else{
		for(int i = 0 ; i < symbolTable.size(); i++){
			if(e.name == symbolTable[i].Name){
				index = i;
				switch(symbolTable[i].DataType){
					case Int:
						e.kind = INT_LITERAL_EXPR;
						break;
					case Float:
						e.kind = FLOAT_LITERAL_EXPR;
						break;
					case Scribble:
						e.kind = SCRIBBLE_LITERAL_EXPR;
						break;
				}
			}
		}
		s = "+" + to_string(symbolTable[index].RelativeAddress) + "(R15)";
	}
}


void CodeGen::DefineVar(ExprRec & exprRec)
{
	exprRec.name = scan.tokenBuffer;
	//Code here
}
void CodeGen::InitializeVar(ExprRec & exprRec)
{
	//Code here

	if(scan.tokenBuffer.length() != 0)
		exprRec.val = stof(scan.tokenBuffer);
	else
		exprRec.val = 0;

	CheckId(exprRec);
}
void CodeGen::FloatAppend()
{
	//Code here
}
void CodeGen::IntAppend()
{
	//Code here
}
void CodeGen::ForAssign()
{
	//Code here
}
void CodeGen::ForUpdate()
{
	//Code here
}
void CodeGen::ForEnd()
{
	//Code here
}
void CodeGen::SetCondition()
{
	//Code here
}
void CodeGen::DoLoopBegin()
{
	//Code here
}
void CodeGen::DoLoopEnd()
{
	//Code here
}
void CodeGen::WhileBegin()
{
	//Code here
}
void CodeGen::WhileEnd()
{
	//Code here
}
void CodeGen::ProcessIf()
{
	//Code here
}
void CodeGen::ProcessElse()
{
	//Code here
}
void CodeGen::IfEnd()
{
	//Code here
}
void CodeGen::Break()
{
	//Code here
}
