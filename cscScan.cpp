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
		if (isspace(currentChar) || multilineComment)
		{
			if (currentChar == '/' && sourceFile.peek() == ':')  // multi line comment end
			{
				multilineComment = false;
				currentChar = NextChar();
			}

				currentChar = NextChar();     // do nothing
		}

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
			if (sourceFile.peek() == ':') // single line comment
				do  // skip comment
					currentChar = NextChar();
				while (currentChar != '\n');
			else if (sourceFile.peek() == '/') // multi line comment start
			{
					multilineComment = true;
			}

			else
			{

				BufferChar(currentChar);
				currentChar = NextChar();

				if(isspace(currentChar))
					return COLON;

				else
				{
					BufferChar(currentChar);
					return CheckReserved();
				}
			}
		}
		else if (isdigit(currentChar))
		{                                // integer literal
			BufferChar(currentChar);
			c = sourceFile.peek();

			DigitWhileLoop(currentChar, c);

			if(c == 'e' || c == 'E')
				return CheckScientificNotation(currentChar, c);

			if(c == '.')
			{
				currentChar = NextChar();
				BufferChar(currentChar);
				c = sourceFile.peek();

				DigitWhileLoop(currentChar, c);

				if(c == 'e' || c == 'E')
					return CheckScientificNotation(currentChar, c);

				return FLOAT_LIT;
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
			if (sourceFile.peek() == ':') // End multiline comment
			{
				cout << "Ending comment" << endl;
				multilineComment = false;
			}
			else if (sourceFile.peek() == '/') // // Integer division
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
		else if (currentChar == '"'){
										// String literal. Handles colons and double quotes
			while(true){
				currentChar = NextChar();
				c = sourceFile.peek();

				if(currentChar != '"')
				{
					if(currentChar == ':')
					{
						BufferChar(':');
					}

					BufferChar(currentChar);

				}
				else
				{
					if(c == '"')
					{
						NextChar();
						BufferChar(':');
						BufferChar('"');
					}
					else
					{
						break;
					}
				}
			}
			BufferChar(char(0));
			return SCRIBBLE_LIT;
		}
		else
			LexicalError(currentChar);
	} // end while
	return EOF_SYM;
}

void Scanner::DigitWhileLoop(char& currentChar, char& c)
{
	while(isdigit(c))
		{
			currentChar = NextChar();
			BufferChar(currentChar);
			c = sourceFile.peek();
		}
}

Token Scanner::CheckScientificNotation(char& currentChar, char& c)
{
	currentChar = NextChar();
	BufferChar(currentChar);
	c = sourceFile.peek();

	if(c == '+' || c == '-')
	{
		currentChar = NextChar();
		BufferChar(currentChar);
		c = sourceFile.peek();

		DigitWhileLoop(currentChar, c);
	}

	else
		DigitWhileLoop(currentChar, c);

	return FLOAT_LIT;
}
