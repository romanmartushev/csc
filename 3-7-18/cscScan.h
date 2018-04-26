/*	____________________________________________________________________________

	                 Scanner Component for the Micro Compiler

	                                mscan.h

	                              Version 2007
 
	                           James L. Richards
	                     Last Update: August 28, 2007

	The routines in this unit are based on those provided in the book 
	"Crafting A Compiler" by Charles N. Fischer and Richard J. LeBlanc, Jr., 
	Benjamin Cummings Publishing Co. (1991).

	See Section 2.2, pp. 25-29.
	____________________________________________________________________________
*/

#ifndef SCANNER
#define SCANNER
#include <string>

const int ID_STRING_LEN = 32;

enum Token  { EOF_SYM, BEGIN_SYM, BREAK_SYM, DO_SYM, FOR_SYM, FLOAT_SYM, FLOATARRAY_SYM,
 INPUT_SYM, INT_SYM, INTARRAY_SYM, NEWLINE_SYM, OUTPUT_SYM, SCRIBBLE_SYM, UNTIL_SYM, WHILE_SYM,
  END_SYM, IF_SYM, ELSE_SYM, ENDSTMT_SYM, LSTAPLE, RSTAPLE, LBANANA,  RBANANA, COLON, SEMICOLON, 
  COMMA, ASSIGN_OP, PLUS_OP,  MINUS_OP, MULT_OP, REALDIV_OP, INTEGERDIV_OP, LT_OP, LE_OP, GT_OP, GE_OP,
   EQ_OP, NE_OP, ID, INT_LIT, FLOAT_LIT, SCRIBBLE_LIT };

class Scanner
{
public:

	string	tokenBuffer, // current token
			lineBuffer;  // current line
	int		lineNumber;  // line counter

	Scanner();
	// Initializes the scanner object.

	Token GetNextToken();
	// Retrieves the next token available in the input stream.

private:
   bool multilineComment = false; //Tracks whether or not the scanner is currently looking through a multiline comment

   void BufferChar(char c);
   // Appends character c to the end of the token buffer provided that the
   // buffer is not full.

   Token CheckReserved();
   // Checks the identifier in the token buffer to see if it is a reserved word
   // or a user-defined identifier and returns the appropriate token.

   void ClearBuffer();
   // Erases the contents of the tokenBuffer.

   void LexicalError(char& c);
   // Processes a lexical error at character c by ignoring that character and 
   // getting the next character.

   char NextChar();
   // Gets next available character from the source file.
};
#endif
