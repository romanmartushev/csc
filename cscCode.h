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


enum OpKind { PLUS, MINUS };

struct OpRec // information about an operator
{
	OpKind op; // operator type
};

enum ExprKind { ID_EXPR, LITERAL_EXPR, TEMP_EXPR };

struct ExprRec // information about a constant, variable, or
               // an intermediate (temporary) result
{
   ExprKind kind;   // operand type
   string   name;   // used when kind is ID_EXPR or TEMP_EXPR
   int      val;    // used when kind is LITERAL_EXPR
};

class CodeGen
{
public:

	CodeGen();
	// Initializes the code generator;

/* _____________________________________________________________________________
*/

	void Assign(const ExprRec & target, const ExprRec & source);
	// Produces the assembly code for an assignment from Source to Target.

	void Finish();
	// Generates code to finish the program.

	void GenInfix(const ExprRec & e1, const OpRec & op,
	              const ExprRec & e2, ExprRec& e);
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

	void InputVar(const ExprRec & InVar);
	// Produces the assembly code for reading a value for InVar.

	void Start();
	// Initializes the compiler.

	void WriteExpr(const ExprRec & OutExpr);
	// Produces the assembly code for writing the value of OutExpr.

	void DefineVar();
	// definition here

	void InitializeVar();
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

	vector<string> symbolTable;

	int  maxTemp;     // max temporary allocated so far; initially 0

	void CheckId(const string & s);
	// Declares s as a new variable and enters it into the symbol table when s
	// is not already in the symbol table.

	void Enter(const string & s);
	// Enters s unconditionally into the symbol table.

	void ExtractExpr(const ExprRec & e, string& s);
	// Returns an operand representation s for the expression e.

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
