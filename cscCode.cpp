/*	____________________________________________________________________________

	    Semantics and Coding Component Implementation for the :Scopy Compiler
	____________________________________________________________________________
*/

#include <iostream>
#include <fstream>
#include <algorithm>
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

void CodeGen::MakeEven(int& number){
	number = number % 2 == 1 ? number += 1 : number;
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
			symbol.NumberOfComponents = s.size;
			symbol.stringValue = s.stringVal;
			symbol.RelativeAddress = stringOffset;
			vector<int> characterLocations;
	    for(int i = 0; i < s.stringVal.length(); i++){
        if(s.stringVal[i] == ':'){
					if(isdigit(s.stringVal[i+1]) && isdigit(s.stringVal[i+2]) && isdigit(s.stringVal[i+3])){
						characterLocations.push_back(i);
					}
					if(s.stringVal[i+1] == ':'){
						characterLocations.push_back(i);
						i++;
					}
				}
			}
			if(characterLocations.size() > 0){
				cout << characterLocations.size() << endl;
				stringOffset += s.size - characterLocations.size()*2;
			}
			else{
				stringOffset += s.size;
			}
			MakeEven(stringOffset);
		break;
	}
	symbol.Name = s.name;
	if(s.kind != SCRIBBLE_LITERAL_EXPR){
		symbol.RelativeAddress = Offset;
		Offset += size;
		MakeEven(Offset);
	}
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
			string s = "There was an issue with code.ExtractOp()!";
			cout << "There was an issue with code.ExtractOp()! The o.kind == " << o.kind << ". The o.op == " << o.op << endl;
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
	int skipSize, memoryUsedByStrings = 0;

	listFile.width(6);
	listFile << ++scan.lineNumber << "  " << scan.lineBuffer << endl;
	Generate("HALT      ", "", "");
	Generate("LABEL     ", "STRINGS", "");
	for(int i = 0; i < symbolTable.size(); i++)
	{
		if(symbolTable[i].DataType == Scribble)
		{
			Generate("STRING    ", "\"" + symbolTable[i].stringValue + "\"", "");
			if(symbolTable[i].stringValue.length() != symbolTable[i].NumberOfComponents){
				skipSize = (symbolTable[i].NumberOfComponents - symbolTable[i].stringValue.length()-1);
				MakeEven(skipSize);
				Generate("SKIP      ", to_string(skipSize), "");
			}
		}
	}
	Generate("LABEL     ", "VARS", "");
	for(int i = 0; i < symbolTable.size(); i++)
	{
		if(symbolTable[i].DataType == Int)
		{
			Generate("INT    ",to_string(symbolTable[i].InitialValue), "");
		}
		if(symbolTable[i].DataType == Float)
		{
			Generate("REAL    ",to_string(symbolTable[i].InitialValue), "");
		}
	}
	outFile.close();
	listFile << endl << endl;
	listFile << " _____________________________________________\n";
	listFile << " <><><><>  V A R I A B L E   T A B L E   <><><><>\n"
		<< endl;
	listFile << " Relative" << endl;
	listFile << " Address      Identifier      Value      Type" << endl;
	listFile << " --------     ----------      -----      -----"
		<< endl;
	for (unsigned i = 0; i < symbolTable.size(); i++)
	{
		if(symbolTable[i].DataType != Scribble)
		{
			listFile.width(7);
			listFile << symbolTable[i].RelativeAddress << "       "<< symbolTable[i].Name << "               "
			<< symbolTable[i].InitialValue << "          " << symbolTable[i].DataType << endl;
		}
	}
	listFile << " _____________________________________________"
		<< endl;
	listFile << endl;
	listFile << " _____________________________________________\n";
	listFile << " <><><><>  S C R I B B L E   T A B L E   <><><><>\n"
		<< endl;
	listFile << " Relative" << endl;
	listFile << " Address      Identifier      Value      Type" << endl;
	listFile << " --------     ----------      -----      -----"
		<< endl;
	for (unsigned i = 0; i < symbolTable.size(); i++)
	{
		if(symbolTable[i].DataType == Scribble)
		{
			listFile.width(7);
			listFile << symbolTable[i].RelativeAddress << "       "<< symbolTable[i].Name << "               "
			<< symbolTable[i].InitialValue << "          " << symbolTable[i].DataType << endl;
		}
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
	if ((e1.name == "int" && e2.name == "int") || (e1.name == "float" && e2.name == "float"))
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
	GetSymbolValue(e, s);
}

void CodeGen::ProcessLit(ExprRec& e)
{
	if(e.kind == SCRIBBLE_LITERAL_EXPR)
	{
		e.stringVal = scan.tokenBuffer.data();
		if(e.name == ""){
			if(e.size == 0)
				e.size = scan.tokenBuffer.length();
			e.name = GetTemp();
			CheckId(e);
		}
	}
	else if(scan.tokenBuffer.find(".") < scan.tokenBuffer.length()
		|| scan.tokenBuffer.find("e") < scan.tokenBuffer.length()
		|| scan.tokenBuffer.find("E") < scan.tokenBuffer.length())
	{
		e.val = atof(scan.tokenBuffer.data());
		if(e.name == ""){
			e.name = GetTemp();
			CheckId(e);
		}
	}
	else
	{
		if(e.name == "")
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
	Generate("LDA       ", "R14", "STRINGS");
}

void CodeGen::WriteExpr(ExprRec & outExpr)
{
	string s;
	GetSymbolValue(outExpr,s);
	if(outExpr.kind == INT_LITERAL_EXPR || outExpr.name == "int")
		Generate("WRI       ", s, "");
	if(outExpr.kind == FLOAT_LITERAL_EXPR || outExpr.name == "float")
		Generate("WRF       ", s, "");
	if(outExpr.kind == SCRIBBLE_LITERAL_EXPR)
		Generate("WRST      ", s, "");
}

void CodeGen::GetSymbolValue(ExprRec& e, string & s)
{
	int index;
	string t;

	if(e.name == "int"){
		IntToAlpha(e.val, t);
		s = "#" + t;
	}else if(e.name == "float"){
		s = "#" + to_string(e.val);
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
		if(e.kind == SCRIBBLE_LITERAL_EXPR)
			s = "+" + to_string(symbolTable[index].RelativeAddress) + "(R14)";
		else
			s = "+" + to_string(symbolTable[index].RelativeAddress) + "(R15)";
	}
}


void CodeGen::DefineVar(ExprRec & exprRec)
{
	exprRec.name = scan.tokenBuffer;
}
void CodeGen::InitializeVar(ExprRec & exprRec)
{
	ExprRec newExpr;
	if(exprRec.kind != SCRIBBLE_LITERAL_EXPR)
	{
		if(scan.tokenBuffer.length() != 0)
			newExpr.val = stof(scan.tokenBuffer);
		else
			newExpr.val = 0;
		CheckId(exprRec);
		if(exprRec.kind == FLOAT_LITERAL_EXPR)
			newExpr.name = "float";
		else
			newExpr.name = "int";
		Assign(exprRec, newExpr);
	}
	else
	{
		exprRec.val = 0;
		CheckId(exprRec);
	}
	newExpr.val = exprRec.val;
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
