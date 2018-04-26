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
		case FLOAT_ARRAY:
			symbol.DataType = Float_Array;
			symbol.NumberOfComponents = s.size;
			symbol.ArrayValues = s.ArrayValues;
			size = s.size * 4;
		break;
		case INT_ARRAY:
			symbol.DataType = Int_Array;
			symbol.NumberOfComponents = s.size;
			symbol.ArrayValues = s.ArrayValues;
			size = s.size * 2;
		break;
		case SCRIBBLE_LITERAL_EXPR:
			symbol.DataType = Scribble;
			symbol.NumberOfComponents = s.size;
			symbol.stringValue = s.stringVal;
			symbol.RelativeAddress = stringOffset;
	    for(int i = 0; i < s.stringVal.length(); i++){
        if(s.stringVal[i] == ':'){
					if(isdigit(s.stringVal[i+1]) && isdigit(s.stringVal[i+2]) && isdigit(s.stringVal[i+3])){
						stringOffset = stringOffset - 3;
					}
					else if(s.stringVal[i+1] == ':'){
						stringOffset = stringOffset;
						i++;
					}else{
						stringOffset = stringOffset - 1;
					}
				}
			}
			if(s.size % 2 == 0){
				stringOffset += s.size+1;
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
			case INTDIV:
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
	if(target.kind == INT_ARRAY){
		GetSymbolValue(source,s);
		Generate("LD        ", "R0", s);
		int t = (int)(target.val*2);
		GetSymbolValue(target,s,t);
		Generate("STO       ", "R0", s);
	}else if(target.kind == FLOAT_ARRAY){
		GetSymbolValue(source,s);
		Generate("LD        ", "R0", s);
		int t = (int)(target.val*4);
		GetSymbolValue(target,s,t);
		Generate("STO       ", "R0", s);
	}else if(target.kind == SCRIBBLE_LITERAL_EXPR){
		StringCpyUsed = true;

		GetSymbolValue(target, s);
		Generate("LD        ", "R0", s);
		GetSymbolValue(source, s);
		Generate("LD        ", "R1", s);
		Generate("JSR       ", "R7", "STRCPY");
	}
	else{
		GetSymbolValue(source,s);
		Generate("LD        ", "R0", s);
		GetSymbolValue(target,s);
		Generate("STO       ", "R0", s);
	}
}


void CodeGen::Finish()
{
	int skipSize, memoryUsedByStrings = 0;

	listFile.width(6);
	listFile << ++scan.lineNumber << "  " << scan.lineBuffer << endl;

	Generate("HALT      ", "", "");

	if(StringCmprUsed)
	{
		Generate("LABEL     ", "STRCMP", "");
		Generate("LD        ", "R0", "*R4");
		Generate("SRZ       ", "R0", "8");

		Generate("LD        ", "R1", "*R5");
		Generate("SRZ       ", "R1", "8");

		Generate("IC        ", "R0", "#0");
		Generate("JEQ       ", "ENDCMP", "");
		Generate("IC        ", "R1", "#0");
		Generate("JEQ       ", "ENDCMP", "");
		Generate("IC        ", "R0", "R1");
		Generate("IA        ", "R4", "#1");
		Generate("IA        ", "R5", "#1");
		Generate("JEQ       ", "STRCMP", "");
		Generate("JMP       ", "*R7", "");

		Generate("LABEL     ", "ENDCMP", "");
		Generate("IC        ", "R0", "R1");
		Generate("JMP       ", "*R7", "");
	}

	if(StringCpyUsed)
	{
		Generate("LABEL     ", "STRCPY", "");
		Generate("LD        ", "R0", "*R4");
		Generate("SRZ       ", "R0", "8");

		Generate("LD        ", "R1", "*R5");
		Generate("SRZ       ", "R1", "8");

		// Generate("IC        ", "R0", "#0");
		// Generate("JEQ       ", "ENDCPY", "");
		Generate("IC        ", "R1", "#0");
		Generate("JEQ       ", "ENDCPY", "");
		Generate("IC        ", "R0", "R1");
		Generate("STO       ", "R0", "R1");
		// Generate("IA        ", "R4", "#1");
		// Generate("IA        ", "R5", "#1");
		Generate("JMP       ", "STRCPY", "");
		Generate("JMP       ", "*R7", "");

		Generate("LABEL     ", "ENDCPY", "");
		Generate("IC        ", "R0", "R1");
		Generate("JMP       ", "*R7", "");
	}

	Generate("LABEL     ", "STRINGS", "");

	for(int i = 0; i < symbolTable.size(); i++)
	{
		if(symbolTable[i].DataType == Scribble)
		{
			Generate("STRING    ", '"' + symbolTable[i].stringValue +'"', "");
			if(symbolTable[i].stringValue.length() != symbolTable[i].NumberOfComponents){
				skipSize = (symbolTable[i].NumberOfComponents - symbolTable[i].stringValue.length());
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
			Generate("INT    ",to_string((int)symbolTable[i].InitialValue), "");
		}

		if(symbolTable[i].DataType == Float)
		{
			Generate("REAL      ",to_string(symbolTable[i].InitialValue), "");
		}
		if(symbolTable[i].DataType == Float_Array)
		{
			while(symbolTable[i].ArrayValues.size() < symbolTable[i].NumberOfComponents){
				symbolTable[i].ArrayValues.push_back(0);
			}
			for(int j = 0; j < symbolTable[i].NumberOfComponents; j++)
			{
				Generate("REAL      ",to_string(symbolTable[i].ArrayValues[j]), "");
			}
		}
		if(symbolTable[i].DataType == Int_Array)
		{
			while(symbolTable[i].ArrayValues.size() < symbolTable[i].NumberOfComponents){
				symbolTable[i].ArrayValues.push_back(0);
			}
			for(int j = 0; j < symbolTable[i].NumberOfComponents; j++)
			{
				Generate("INT      ",to_string((int)symbolTable[i].ArrayValues[j]), "");
			}
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

void CodeGen::GenInfix(ExprRec & e1, OpRec & op, ExprRec & e2, ExprRec& e)
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
		case	INTDIV:
			e.val = floor (e1.val/e2.val);
			break;
		case GE:
		case GT:
		case LE:
		case LT:
		case EQ:
		case NE:
		break;
		}
	}
	else
	{
		e.name = GetTemp();
		CheckId(e);
		e.val = 0;
		GetSymbolValue(e1,opnd);

		if(e1.kind == FLOAT_LITERAL_EXPR || e2.kind == FLOAT_LITERAL_EXPR)
			op.kind = FLOAT_LITERAL_EXPR;
		else
			op.kind = INT_LITERAL_EXPR;

		if(e1.name == "int" && (e1.kind == FLOAT_LITERAL_EXPR || e2.kind == FLOAT_LITERAL_EXPR))
			Generate("FLT       ", "R0", opnd);
		else{
			Generate("LD        ", "R0", opnd);

		}
		GetSymbolValue(e2,opnd);

		string operation = ExtractOp(op);

		if(e2.name == "int" && (e1.kind == FLOAT_LITERAL_EXPR || e2.kind == FLOAT_LITERAL_EXPR)){
			Generate("FLT       ", "R1", opnd);
			Generate(operation, "R0", "R1");
		}
		else
			Generate(operation, "R0", opnd);



		if(op.op == INTDIV){
			std::cout << opnd << '\n';
			Generate("FIX       ", "R2", "R0");

			e.name = "convertedInt";
			e.kind = INT_LITERAL_EXPR;
			GetSymbolValue(e,opnd);
			Generate("STO       ", "R2", opnd);
		}else{
			GetSymbolValue(e,opnd);
			Generate("STO       ", "R0", opnd);
		}
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
		if(e.name == "")
		{
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
		if(e.name == "")
		{
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
	else if (scan.tokenBuffer == "//")
		o.op = INTDIV;
	else if (scan.tokenBuffer == ">")
		o.op = GT;
	else if (scan.tokenBuffer == ">=")
		o.op = GE;
	else if (scan.tokenBuffer == "<")
		o.op = LT;
	else if (scan.tokenBuffer == "<=")
		o.op = LE;
	else if (scan.tokenBuffer == "==")
		o.op = EQ;
	else if (scan.tokenBuffer == "!=")
		o.op = NE;
}

void CodeGen::InputVar(ExprRec & inVar)
{
	string s;
	int t;
	if(inVar.kind == INT_ARRAY){
		t = (int)inVar.val*2;
		GetSymbolValue(inVar,s,t);
		Generate("RDI       ", s, "");
	}else if(inVar.kind == FLOAT_ARRAY){
		t = (int)inVar.val*4;
		GetSymbolValue(inVar,s,t);
		Generate("RDF       ", s, "");
	}else{
		GetSymbolValue(inVar,s);
		if(inVar.kind == INT_LITERAL_EXPR)
			Generate("RDI       ", s, "");
		if(inVar.kind == FLOAT_LITERAL_EXPR)
			Generate("RDF       ", s, "");
	}

}

void CodeGen::Start()
{
	Generate("LDA       ", "R15", "VARS");
	Generate("LDA       ", "R14", "STRINGS");
}

void CodeGen::WriteExpr(ExprRec & outExpr)
{
	string s;
	int t;
	if(outExpr.kind == INT_ARRAY){
		t = (int)outExpr.val*2;
		GetSymbolValue(outExpr,s,t);
		Generate("WRI       ", s, "");
	}else if(outExpr.kind == FLOAT_ARRAY){
		t = (int)outExpr.val*4;
		GetSymbolValue(outExpr,s,t);
		Generate("WRF       ", s, "");
	}else{
		GetSymbolValue(outExpr,s);
		if(outExpr.kind == INT_LITERAL_EXPR && outExpr.name == "convertedInt")
			Generate("WRI       ", s, "");
		else{
			if(outExpr.kind == INT_LITERAL_EXPR || outExpr.name == "int")
				Generate("WRI       ", s, "");
			if(outExpr.kind == FLOAT_LITERAL_EXPR || outExpr.name == "float"){
				Generate("WRF       ", s, "");
			}
			if(outExpr.kind == SCRIBBLE_LITERAL_EXPR)
				Generate("WRST      ", s, "");
		}
	}
}

void CodeGen::GetSymbolValue(ExprRec& e, string & s, int arrayOffset)
{
	int index;
	string t;

	if(e.name == "int"){
		s = "#" + to_string((int)e.val);
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
					case Int_Array:
						e.kind = INT_ARRAY;
						break;
					case Float_Array:
						e.kind = FLOAT_ARRAY;
						break;
				}
			}
		}
		if(e.kind == SCRIBBLE_LITERAL_EXPR)
			s = "+" + to_string(symbolTable[index].RelativeAddress) + "(R14)";
		else
			s = "+" + to_string(symbolTable[index].RelativeAddress + arrayOffset) + "(R15)";
	}
}


void CodeGen::DefineVar(ExprRec & exprRec)
{
	exprRec.name = scan.tokenBuffer;
}
void CodeGen::InitializeVar(ExprRec & exprRec)
{
	ExprRec newExpr;
	if(exprRec.kind != FLOAT_ARRAY && exprRec.kind != INT_ARRAY){
		if(exprRec.kind != SCRIBBLE_LITERAL_EXPR)
		{
			if(scan.tokenBuffer.length() != 0){
				newExpr.val = stof(scan.tokenBuffer);
				exprRec.val = stof(scan.tokenBuffer);
			}
			else{
				exprRec.val = 0;
				newExpr.val = 0;
			}
			CheckId(exprRec);
			if(exprRec.kind == FLOAT_LITERAL_EXPR)
				newExpr.name = "float";
			else
			{
				newExpr.name = "int";
				Assign(exprRec, newExpr);
			}
		}
		else
		{
			exprRec.val = 0;
			CheckId(exprRec);
		}
		newExpr.val = exprRec.val;
	}else{
		CheckId(exprRec);
	}
}

void CodeGen::FloatAppend(ExprRec & exprRec)
{
	exprRec.ArrayValues.push_back(stof(scan.tokenBuffer.data()));
}
void CodeGen::IntAppend(ExprRec & exprRec)
{
	exprRec.ArrayValues.push_back(stof(scan.tokenBuffer.data()));
}
void CodeGen::ForAssign(ExprRec& expr, ExprRec& expr2)
{
	Assign(expr,expr2);
}
void CodeGen::ForBegin()
{
	int type = 4;
	StackType.push_back(type);
	StatementCounter++;
	Stack.push_back(StatementCounter);
	Generate("LABEL     ", "FUP" + to_string(Stack.back()), "");
}

void CodeGen::ForUpdate(OpRec& op)
{
	switch (op.op)
	{
		case GE:
			Generate("JLT       ", "FEND" + to_string(Stack.back()), "");
			break;
		case GT:
			Generate("JLE       ", "FEND" + to_string(Stack.back()), "");
			break;
		case LE:
			Generate("JGT       ", "FEND" + to_string(Stack.back()), "");
			break;
		case LT:
			Generate("JGE       ", "FEND" + to_string(Stack.back()), "");
			break;
		case EQ:
			Generate("JNE       ", "FEND" + to_string(Stack.back()), "");
			break;
		case NE:
			Generate("JEQ       ", "FEND" + to_string(Stack.back()), "");
			break;
		break;
	}


}
void CodeGen::ForEnd()
{
	Generate("JMP       ", "FUP" + to_string(Stack.back()), "");
	Generate("LABEL     ", "FEND" + to_string(Stack.back()), "");

	Stack.pop_back();
	StackType.pop_back();
}
void CodeGen::SetCondition(ExprRec& leftHandSide, ExprRec& rightHandSide)
{
	string s, t;

	if(leftHandSide.kind == INT_LITERAL_EXPR && rightHandSide.kind == INT_LITERAL_EXPR)
	{
		GetSymbolValue(leftHandSide, s);
		Generate("LD        ", "R0", s);
		GetSymbolValue(rightHandSide, s);
		Generate("IC        ", "R0", s);
	}

	if(leftHandSide.kind == FLOAT_LITERAL_EXPR && rightHandSide.kind == FLOAT_LITERAL_EXPR)
	{
		GetSymbolValue(leftHandSide, s);
		Generate("LD        ", "R0", s);
		GetSymbolValue(rightHandSide, s);
		Generate("FC        ", "R0", s);
	}

	if(leftHandSide.kind == INT_LITERAL_EXPR && rightHandSide.kind == FLOAT_LITERAL_EXPR)
	{
		GetSymbolValue(leftHandSide, s);
		Generate("FLT       ", "R1", s);
		GetSymbolValue(rightHandSide, s);
		Generate("FC        ", "R1", s);
	}

	if(leftHandSide.kind == FLOAT_LITERAL_EXPR && rightHandSide.kind == INT_LITERAL_EXPR)
	{
		GetSymbolValue(leftHandSide, s);
		Generate("LD        ", "R0", s);
		GetSymbolValue(rightHandSide, s);
		Generate("FLT       ", "R2", s);
		Generate("FC        ", "R0", "R2");
	}

	if(leftHandSide.kind == SCRIBBLE_LITERAL_EXPR || rightHandSide.kind == SCRIBBLE_LITERAL_EXPR)
	{
		StringCmprUsed = true;

		GetSymbolValue(leftHandSide, s);
		Generate("LD        ", "R0", s);
		GetSymbolValue(rightHandSide, s);
		Generate("LD        ", "R1", s);
		Generate("JSR       ", "R7", "STRCMP");
	}
}

void CodeGen::DoLoopBegin()
{
	int type = 3;
	StackType.push_back(type);
	StatementCounter++;
	Stack.push_back(StatementCounter);
	Generate("LABEL     ", "DOUT" + to_string(Stack.back()), "");
}
void CodeGen::DoLoopEnd(OpRec& op)
{
	switch (op.op)
	{
		case GE:
			Generate("JLT       ", "DOUT" + to_string(Stack.back()), "");
			break;
		case GT:
			Generate("JLE       ", "DOUT" + to_string(Stack.back()), "");
			break;
		case LE:
			Generate("JGT       ", "DOUT" + to_string(Stack.back()), "");
			break;
		case LT:
			Generate("JGE       ", "DOUT" + to_string(Stack.back()), "");
			break;
		case EQ:
			Generate("JNE       ", "DOUT" + to_string(Stack.back()), "");
			break;
		case NE:
			Generate("JEQ       ", "DOUT" + to_string(Stack.back()), "");
			break;
		break;
	}
	Generate("LABEL     ", "DOEND" + to_string(Stack.back()), "");
	Stack.pop_back();
	StackType.pop_back();
}
void CodeGen::WhileLabeling()
{
	int type = 2;
	StackType.push_back(type);
	StatementCounter++;
	Stack.push_back(StatementCounter);
	Generate("LABEL     ", "WHLBEG" + to_string(Stack.back()), "");
}
void CodeGen::WhileBegin(OpRec& op)
{
	switch (op.op)
	{
		case GE:
			Generate("JLT       ", "WHLEND" + to_string(Stack.back()), "");
			break;
		case GT:
			Generate("JLE       ", "WHLEND" + to_string(Stack.back()), "");
			break;
		case LE:
			Generate("JGT       ", "WHLEND" + to_string(Stack.back()), "");
			break;
		case LT:
			Generate("JGE       ", "WHLEND" + to_string(Stack.back()), "");
			break;
		case EQ:
			Generate("JNE       ", "WHLEND" + to_string(Stack.back()), "");
			break;
		case NE:
			Generate("JEQ       ", "WHLEND" + to_string(Stack.back()), "");
			break;
		default:
			//Generate("OH SHIT","","");
			break;
	}

}
void CodeGen::WhileEnd()
{
	Generate("JMP       ", "WHLBEG" + to_string(Stack.back()), "");
	Generate("LABEL     ", "WHLEND" + to_string(Stack.back()), "");
	Stack.pop_back();
	StackType.pop_back();
}
void CodeGen::ProcessIf(OpRec& op)
{
	StatementCounter2++;
	ColtonWasHere.push_back(StatementCounter2);
	switch (op.op)
	{
		case GE:
			Generate("JLT       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case GT:
			Generate("JLE       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case LE:
			Generate("JGT       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case LT:
			Generate("JGE       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case EQ:
			Generate("JNE       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case NE:
			Generate("JEQ       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		break;
	}
}
void CodeGen::ProcessElse(OpRec& op)
{
	Generate("LABEL     ", "IFEND" + to_string(ColtonWasHere.back()), "");
	ColtonWasHere.pop_back();
	StatementCounter2++;
	ColtonWasHere.push_back(StatementCounter2);
	switch (op.op)
	{
		case GE:
			Generate("JGE       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case GT:
			Generate("JGT       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case LE:
			Generate("JLE       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case LT:
			Generate("JLT       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case EQ:
			Generate("JEQ       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		case NE:
			Generate("JNE       ", "IFEND" + to_string(ColtonWasHere.back()), "");
			break;
		break;
	}
}
void CodeGen::IfEnd()
{
	Generate("LABEL     ", "IFEND" + to_string(ColtonWasHere.back()), "");
	ColtonWasHere.pop_back();
}
void CodeGen::Break()
{
	switch( StackType.back()){
		case 2:
			Generate("JMP       ", "WHLEND" + to_string(Stack.back()), "");
			break;
		case 3:
			Generate("JMP       ", "DOEND" + to_string(Stack.back()), "");
			break;
		case 4:
			Generate("JMP       ", "FOREND" + to_string(Stack.back()), "");
			break;
	}

}
