/*	____________________________________________________________________________

	           Semantics and Coding Component for the :Scopy Compiler
	____________________________________________________________________________
*/

#ifndef CODEGEN
#define CODEGEN

#include <string>
#include <vector>
using namespace std;

#include "cscScan.h"
#include "cscSymbol.h"
#include "cscSymbol.h"

enum OpKind { PLUS, MINUS, MULTIPLY, DIVIDE };
enum ExprKind { ID_EXPR, LITERAL_EXPR, TEMP_EXPR, INT_LITERAL_EXPR, FLOAT_LITERAL_EXPR, SCRIBBLE_LITERAL_EXPR };

struct OpRec // information about an operator
{
	ExprKind kind; //used for distinguishing float or int arithmetic
	OpKind op; // operator type
};


struct ExprRec // information about a constant, variable, or
               // an intermediate (temporary) result
{
   ExprKind kind;   // operand type
   string   name;   // used when kind is ID_EXPR or TEMP_EXPR or FLOAT_LITERAL_EXPR or INT_LITERAL_EXPR
   float      val;    // used when kind is ID_EXPR or TEMP_EXPR or FLOAT_LITERAL_EXPR or INT_LITERAL_EXPR
   int size = 0; //Contains size of scribbles and arrays
   string stringVal; //Used in scribbles (strings)
};

class CodeGen
{
public:
	int Offset = 0;
	int stringOffset = 0;
	CodeGen();
	// Initializes the code generator;

/* _____________________________________________________________________________
*/
	void MakeEven(int& number);
	void GetSymbolValue(ExprRec & e, string & s);
	// sets the kind of incoming symbol to the previsouly declared type
	// Returns the offset of a variable in the symbolTable

	void Assign(ExprRec & target, ExprRec & source);
	// Produces the assembly code for an assignment from Source to Target.

	void Finish();
	// Generates code to finish the program.

	void GenInfix(ExprRec & e1, const OpRec & op, ExprRec & e2, ExprRec& e);
	// Produces the assembly code for an infix operation.

	void NewLine();
	// Produces the assembly code for starting a new output line.

	void ProcessVar(ExprRec& e);
	// Declares the variable in the token buffer and builds a
	// corresponding semantic record e.

	void ProcessLit(ExprRec& e);
	// Converts the literal found in the token buffer into numeric form
	// and builds a corresponding semantic record e.

	void ProcessOp(OpRec& o);
	// Produces an operator descriptor O for the operator in the token
	// buffer.

	void InputVar(ExprRec & InVar);
	// Produces the assembly code for reading a value for InVar.

	void Start();
	// Initializes the compiler.

	void WriteExpr(ExprRec & OutExpr);
	// Produces the assembly code for writing the value of OutExpr.

	void DefineVar(ExprRec & exprRec);
	// definition here

	void InitializeVar(ExprRec & exprRec);
	// definition here

	void FloatAppend();
	// definition here

	void IntAppend();
	// definition here

	void ForAssign();
	// definition here

	void ForUpdate();
	// definition here

	void ForEnd();
	// definition here

	void SetCondition();
	// definition here

	void DoLoopBegin();
	// definition here

	void DoLoopEnd();
	// definition here

	void WhileBegin();
	// definition here

	void WhileEnd();
	// definition here

	void ProcessIf();
	// definition here

	void ProcessElse();
	// definition here

	void IfEnd();
	// definition here

	void Break();
	// definition here

/* _____________________________________________________________________________
*/

private:

	vector<Symbol> symbolTable;

	int  maxTemp;     // max temporary allocated so far; initially 0

	void CheckId(const ExprRec & exprRec);
	// Checks to see if a ExprRec was enter into the symbolTable
	// IF not it calls Enter

	void Enter(const ExprRec & s);
	// Enters s unconditionally into the symbol table.

	string ExtractOp(const OpRec& o);
	// Returns a representation for the operator o.

	void Generate(const string & s1, const string & s2, const string & s3);
	// Produces the SAM assembly code for one or two operand instructions.
	// s1 is the opcode; s2 and s3 are operands.

	string GetTemp();
	// Creates a temporary variable and returns its name.

	void IntToAlpha(int val, string& str);
	// Makes a string representation for a positive integer val.

	bool LookUp(const string &s);
	// Returns true if s is in the symbol table; otherwise,
	// false is returned.
};

#endif
