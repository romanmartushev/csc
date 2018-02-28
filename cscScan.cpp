/*	____________________________________________________________________________

	         Scanner Component Implementation for the :Scopy Compiler
	____________________________________________________________________________
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern ifstream sourceFile;
extern ofstream outFile, listFile;

#include "cscScan.h"

// *******************
// **  Constructor  **
// *******************

Scanner::Scanner()
{
	tokenBuffer = "";
	lineBuffer = "";
	lineNumber = 0;
}

// ********************************
// **  Private Member Functions  **
// ********************************

void Scanner::BufferChar(char c)
{
	if (tokenBuffer.length() < ID_STRING_LEN)
		tokenBuffer += c;
}

Token Scanner::CheckReserved()
{
	if (tokenBuffer == ":A") return BEGIN_SYM;
	if (tokenBuffer == ":Z") return END_SYM;
	if (tokenBuffer == ":I") return INPUT_SYM;
	if (tokenBuffer == ":O") return OUTPUT_SYM;
	if (tokenBuffer == ":B") return BREAK_SYM;
	if (tokenBuffer == ":D") return DO_SYM;
	if (tokenBuffer == ":F") return FOR_SYM;
	if (tokenBuffer == ":U") return UNTIL_SYM;
	if (tokenBuffer == ":W") return WHILE_SYM;
	if (tokenBuffer == ":?") return IF_SYM;
	if (tokenBuffer == ":!") return ELSE_SYM;
	if (tokenBuffer == ":.") return ENDSTMT_SYM;
	if (tokenBuffer == ":=") return ASSIGN_OP;
	if (tokenBuffer == ":") return COLON;
	if (tokenBuffer == ":N") return NEWLINE_SYM;
	if (tokenBuffer == "int") return INT_SYM;
  if (tokenBuffer =="float") return FLOAT_SYM;
  if (tokenBuffer =="floatarray") return FLOATARRAY_SYM;
  if (tokenBuffer =="intarray") return INTARRAY_SYM;
  if (tokenBuffer =="scribble") return SCRIBBLE_SYM;

	return ID;
}

void Scanner::ClearBuffer()
{
	tokenBuffer = "";
}

void Scanner::LexicalError(char& c)
{
	cout << " *** Lexical Error: '" << c
		<< "' ignored at position " << int(lineBuffer.size())
		<< " on line #" << lineNumber+1 << '.' << endl;
	listFile << " *** Lexical Error: '" << c
		<< "' ignored at position " << int(lineBuffer.size())
		<< " on line #" << lineNumber+1 << '.' << endl;
	c = NextChar();
}

char Scanner::NextChar()
{
	char c;

	sourceFile.get(c);
	if (c == '\n')
	{
		listFile.width(6);
		listFile << ++lineNumber << "  " << lineBuffer << endl;
		lineBuffer = "";
	}
	else
		lineBuffer += c;
	return c;
}

// *******************************
// **  Public Member Functions  **
// *******************************

Token Scanner::GetNextToken()
{
	char currentChar, c;

	ClearBuffer();
	currentChar = NextChar();
	while (!sourceFile.eof())
	{
		if (isspace(currentChar))
			currentChar = NextChar();     // do nothing
		else if (isalpha(currentChar))
		{                                // identifier
			BufferChar(currentChar);
			c = sourceFile.peek();
			while (isalnum(c) || c == '_')
			{
				currentChar = NextChar();
				BufferChar(currentChar);
				c = sourceFile.peek();
			}
			return CheckReserved();
		}
		else if (currentChar == ':')
		{
			BufferChar(currentChar);
			c = sourceFile.peek();
			if (c == ':'){
				while(c != '\n'){
					currentChar = NextChar();
					c = sourceFile.peek();
				}
				ClearBuffer();
				currentChar = NextChar();
			}else if(c == '/'){
				while(true){
					currentChar = NextChar();
					c = sourceFile.peek();
					if(currentChar == '/' && c == ':')
						break;
				}
				currentChar = NextChar();
				ClearBuffer();
				currentChar = NextChar();
			}else if(isspace(c)){
					return CheckReserved();
			}else{
				currentChar = NextChar();
				BufferChar(currentChar);
				return CheckReserved();
			}
		}
		else if (isdigit(currentChar))
		{                                // integer literal
			BufferChar(currentChar);
			c = sourceFile.peek();
			while (isdigit(c))
			{
				currentChar = NextChar();
				BufferChar(currentChar);
				c = sourceFile.peek();
			}
			return INT_LIT;
		}
		else if (currentChar == '[')
			return LSTAPLE;
		else if (currentChar == ']')
			return RSTAPLE;
		else if (currentChar == '(')
			return LBANANA;
		else if (currentChar == ')')
			return RBANANA;
		else if (currentChar == ';')
			return SEMICOLON;
		else if (currentChar == ',')
			return COMMA;
		else if (currentChar == '+')
		{
			BufferChar(currentChar);
			return PLUS_OP;
		}
		else if (currentChar == '/')
			if (sourceFile.peek() == '/') // // Integer division
			{
				currentChar = NextChar();
				return INTEGERDIV_OP;
			}
			else { //Real division
				BufferChar(currentChar);
				return REALDIV_OP;
			}
		else if (currentChar == '-')
		{
			BufferChar(currentChar);      // minus operator
			return MINUS_OP;
		}
		else if (currentChar == '=') // == EQ_OP
		{
			if(sourceFile.peek() == '=')
			{
				currentChar = NextChar();
				return EQ_OP;
			}
		}
		else if (currentChar == '>')
			if (sourceFile.peek() == '=') // >= GE_OP
			{
				currentChar = NextChar();
				return GE_OP;
			}
			else { // > GT_OP
				BufferChar(currentChar);
				return GT_OP;
			}
		else if (currentChar == '<')
			if (sourceFile.peek() == '=') // >= LE_OP
			{
				currentChar = NextChar();
				return LE_OP;
			}
			else { // < LT_OP
				BufferChar(currentChar);
				return LT_OP;
			}
		else if (currentChar == '!')
		{
			if(sourceFile.peek() == '=') // != NE_OP
			{
				currentChar = NextChar();
				return NE_OP;
			}
		}
		else if (currentChar == '*') // * MULT_OP
		{
			BufferChar(currentChar);
			return MULT_OP;
		}
		else if (currentChar == ',') // , COMMA
		{
			BufferChar(currentChar);
			return COMMA;
		}
		else
			LexicalError(currentChar);
	} // end while
	return EOF_SYM;
}
