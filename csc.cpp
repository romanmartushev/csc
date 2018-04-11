/*	____________________________________________________________________________

                      : S C O P Y   C O M P I L E R
						         -- Generates SAM Assembly Code --
	____________________________________________________________________________
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

                     // GLOBAL FILE STREAMS
ifstream sourceFile; // source program
ofstream outFile,    // object program
         listFile;   // compiler listing

#include "cscScan.h"   // scanner component definition
#include "cscParse.h"	 // parser component definition
#include "cscCode.h"   // code generator component definition

                     // GLOBAL COMPONENT OBJECTS
Scanner scan;        // scanner
Parser parse;        // parser
CodeGen code;        // code generator

string Date();
// Returns the current date.

string Time();
// Returns the current time.

int main(int argc, char* argv[])
{
	string sourceName, outName, listName;

	cout
		<< "\n"
		<< " : S C O P Y   C O M P I L E R   2 0 1 8\n"
		<< " _____________________________________\n"
		<< endl;
        if (argc == 2){
          sourceName = argv[1];
        }
        else {
	  cout << " Source file (.sy extension is assumed): ";
	  getline(cin, sourceName);
	}

   // Add appropriate extensions to file names.
	outName = sourceName + ".asm";
	listName = sourceName + ".lst";
	sourceName += ".sy";

   // Open and initialize all files.
	sourceFile.open(sourceName.data());
	if (!sourceFile.is_open())
	{
		cout << "\n File not found. Compilation aborted!\n\n";
		exit(1);
	}
	outFile.open(outName.data());
	listFile.open(listName.data());

	listFile
		<< "\n\n : S C O P Y   C O M P I L E R   L I S T I N G\n\n"
		<< " Generated code is SAM assembly language for\n"
		<< " the MACC2 virtual computer.\n"
		<< " ___________________________________________\n\n";
	listFile << ' ' + Date() << " at " << Time() << endl;
	listFile << " Source file: " << sourceName << endl << endl;
	listFile << " LINE #" << endl;

	parse.SystemGoal();
  /**
  *This block was used for testing the Scanner, making sure it was
  *corecctly classifiying the tokens provided.
  */
	Token scanToken = scan.GetNextToken();
	while(scanToken != EOF_SYM){
    string token;
    switch(scanToken){
      case 1: token = "BEGIN_SYM"; break;
      case 2: token = "BREAK_SYM"; break;
      case 3: token = "DO_SYM"; break;
      case 4: token = "FOR_SYM"; break;
      case 5: token = "FLOAT_SYM"; break;
      case 6: token = "FLOATARRAY_SYM"; break;
      case 7: token = "INPUT_SYM"; break;
      case 8: token = "INT_SYM"; break;
      case 9: token = "INTARRAY_SYM"; break;
      case 10: token = "NEWLINE_SYM"; break;
      case 11: token = "OUTPUT_SYM"; break;
      case 12: token = "SCRIBBLE_SYM"; break;
      case 13: token = "UNTIL_SYM"; break;
      case 14: token = "WHILE_SYM"; break;
      case 15: token = "END_SYM"; break;
      case 16: token = "IF_SYM"; break;
      case 17: token = "ELSE_SYM"; break;
      case 18: token = "ENDSTMT_SYM"; break;
      case 19: token = "LSTAPLE"; break;
      case 20: token = "RSTAPLE"; break;
      case 21: token = "LBANANA"; break;
      case 22: token = "RBANANA"; break;
      case 23: token = "COLON"; break;
      case 24: token = "SEMICOLON"; break;
      case 25: token = "COMMA"; break;
      case 26: token = "ASSIGN_OP"; break;
      case 27: token = "PLUS_OP"; break;
      case 28: token = "MINUS_OP"; break;
      case 29: token = "MULT_OP"; break;
      case 30: token = "REALDIV_OP"; break;
      case 31: token = "INTEGERDIV_OP"; break;
      case 32: token = "LT_OP"; break;
      case 33: token = "LE_OP"; break;
      case 34: token = "GT_OP"; break;
      case 35: token = "GE_OP"; break;
      case 36: token = "EQ_OP"; break;
      case 37: token = "NE_OP"; break;
      case 38: token = "ID"; break;
      case 39: token = "INT_LIT"; break;
      case 40: token = "FLOAT_LIT"; break;
      case 41: token = "SCRIBBLE_LIT"; break;
      default: token = "EOF_SYM"; break;
    }
		cout << scan.tokenBuffer << " " << token << endl;
		scanToken = scan.GetNextToken();
	}
	cout << endl
		<< "\n Successful Compilation\n"
		<< "\n Object code --> " << outName << endl
		<< "\n Listing file --> " << listName << endl << endl;
	return 0;
}

string Date()
{
	const time_t current_time = time (NULL);
	char the_date[20];

	strftime (the_date, 20, "%B %d, %Y", localtime (&current_time));

	return the_date;
}

string Time()
{
	const time_t current_time = time (NULL);
	char the_time[10];


	strftime (the_time, 10, "%I:%M %p", localtime (&current_time));

	return the_time;
}
