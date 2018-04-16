// :Scopy Grammar 2018
//
// Parser Class Implementation File

// SHELL GENERATED BY PARSERGEN VERSION 5.0.4

#include <iostream>
#include <string>
using namespace std;

#include "cscParse.h"
#include "cscCode.h"
#include "cscScan.h"

extern Scanner scan;
extern CodeGen code;

Parser::Parser()
{
	tokenAvailable = false;
}

void Parser::SyntaxError(Token t, string msg)
{
	cout << t << endl;
	cout << "Syntax Error: " + msg << " line number: " << scan.lineNumber << endl;
	exit(1); // abort on any syntax error
}

Token Parser::NextToken()
{
	if (!tokenAvailable)
	{
		savedToken = scan.GetNextToken();
		tokenAvailable = true;
	}
	return savedToken;
}

void Parser::Match(Token t)
{
	if (t != NextToken())
		SyntaxError(t, "");
	else
		tokenAvailable = false;
}


void Parser::ListType(ExprRec & exprRec)
{
	switch (NextToken())
	{
	case FLOAT_LIT:
		FloatList(exprRec);
		break;
	case INT_LIT:
		IntList(exprRec);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::InitValue(ExprRec& exprRec)
{
	switch (NextToken())
	{
	case INT_LIT:
	case FLOAT_LIT:
	case SCRIBBLE_LIT:
		Literal(exprRec);
		code.ProcessLit(exprRec);
		break;
	case LSTAPLE:
		Match(LSTAPLE);
		ListType(exprRec);
		Match(RSTAPLE);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarDecTail(ExprRec& exprRec)
{
	ExprRec rec;
	switch (NextToken())
	{
	case COMMA:
		rec.kind = exprRec.kind;
		Match(COMMA);
		Match(ID);
		code.DefineVar(rec);
		Init(rec);
		code.InitializeVar(rec);
		VarDecTail(exprRec);
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Init(ExprRec& exprRec)
{
	switch (NextToken())
	{
	case ASSIGN_OP:
		Match(ASSIGN_OP);
		InitValue(exprRec);
		break;
	case SEMICOLON:
	case COMMA:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarDecList(ExprRec& exprRec)
{
	Match(ID);
	code.DefineVar(exprRec);
	Init(exprRec);
	code.InitializeVar(exprRec);
	VarDecTail(exprRec);
}

void Parser::DecTail()
{
	switch (NextToken())
	{
	case FLOAT_SYM:
	case FLOATARRAY_SYM:
	case INT_SYM:
	case INTARRAY_SYM:
	case SCRIBBLE_SYM:
		Declaration();
		DecTail();
		break;
	case BREAK_SYM:
	case DO_SYM:
	case FOR_SYM:
	case INPUT_SYM:
	case NEWLINE_SYM:
	case OUTPUT_SYM:
	case WHILE_SYM:
	case IF_SYM:
	case ID:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Declaration()
{
	ExprRec rec;

	Type(rec);
	Match(COLON);
	VarDecList(rec);
	Match(SEMICOLON);
}

void Parser::ScribbleType(ExprRec& expr)
{
	Match(SCRIBBLE_SYM);
	SizeSpec(expr);
}

void Parser::SizeSpec(ExprRec& expr)
{
	switch (NextToken())
	{
	case LSTAPLE:
		Match(LSTAPLE);
		Match(INT_LIT);
		expr.size = atoi(scan.tokenBuffer.data());
		Match(RSTAPLE);
		break;
	case COLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Type(ExprRec& exprRec)
{
	switch (NextToken())
	{
	case INT_SYM:
		Match(INT_SYM);
		exprRec.kind = INT_LITERAL_EXPR;
		break;
	case FLOAT_SYM:
		Match(FLOAT_SYM);
		exprRec.kind = FLOAT_LITERAL_EXPR;
		break;
	case INTARRAY_SYM:
		Match(INTARRAY_SYM);
		exprRec.kind = INT_ARRAY;
		SizeSpec(exprRec);
		break;
	case FLOATARRAY_SYM:
		Match(FLOATARRAY_SYM);
		exprRec.kind = FLOAT_ARRAY;
		SizeSpec(exprRec);
		break;
	case SCRIBBLE_SYM:
		exprRec.kind = SCRIBBLE_LITERAL_EXPR;
		ScribbleType(exprRec);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Literal(ExprRec& expr)
{
	switch (NextToken())
	{
	case INT_LIT:
		Match(INT_LIT);
		expr.kind = INT_LITERAL_EXPR;
		break;
	case FLOAT_LIT:
		Match(FLOAT_LIT);
		expr.kind = FLOAT_LITERAL_EXPR;
		break;
	case SCRIBBLE_LIT:
		Match(SCRIBBLE_LIT);
		expr.kind = SCRIBBLE_LITERAL_EXPR;
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::MultOp()
{
	switch (NextToken())
	{
	case MULT_OP:
		Match(MULT_OP);
		break;
	case REALDIV_OP:
		Match(REALDIV_OP);
		break;
	case INTEGERDIV_OP:
		Match(INTEGERDIV_OP);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::FactorTail(ExprRec& expr)
{
	ExprRec leftOperand, rightOperand;
	OpRec op;

	switch (NextToken())
	{
	case MULT_OP:
	case REALDIV_OP:
	case INTEGERDIV_OP:
		leftOperand.kind = expr.kind;
		leftOperand.val = expr.val;
		leftOperand.name = expr.name;
		MultOp();
		code.ProcessOp(op);
		Primary(rightOperand);
		code.GenInfix(leftOperand,op,rightOperand,expr);
		FactorTail(expr);
		break;
	case RSTAPLE:
	case RBANANA:
	case SEMICOLON:
	case COMMA:
	case PLUS_OP:
	case MINUS_OP:
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP:
	case NE_OP:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Primary(ExprRec& expr)
{
	switch (NextToken())
	{
	case INT_LIT:
	case FLOAT_LIT:
	case SCRIBBLE_LIT:
		Literal(expr);
		code.ProcessLit(expr);
		break;
	case ID:
		Variable(expr);
		//code.ProcessVar(expr);
		break;
	case LBANANA:
		Match(LBANANA);
		Expression(expr);
		Match(RBANANA);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::AddOp()
{
	switch (NextToken())
	{
	case PLUS_OP:
		Match(PLUS_OP);
		break;
	case MINUS_OP:
		Match(MINUS_OP);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::ExprTail(ExprRec& expr)
{
	ExprRec leftOperand, rightOperand;
	OpRec op;
	switch (NextToken())
	{
	case PLUS_OP:
	case MINUS_OP:
		leftOperand.kind = expr.kind;
		leftOperand.val = expr.val;
		leftOperand.name = expr.name;
		AddOp();
		code.ProcessOp(op);
		Factor(rightOperand);
		code.GenInfix(leftOperand,op,rightOperand,expr);
		ExprTail(expr);
		break;
	case RSTAPLE:
	case RBANANA:
	case SEMICOLON:
	case COMMA:
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP:
	case NE_OP:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Factor(ExprRec& expr)
{
	Primary(expr);
	FactorTail(expr);

}

void Parser::RelOp()
{
	switch (NextToken())
	{
	case LT_OP:
		Match(LT_OP);
		break;
	case LE_OP:
		Match(LE_OP);
		break;
	case GT_OP:
		Match(GT_OP);
		break;
	case GE_OP:
		Match(GE_OP);
		break;
	case EQ_OP:
		Match(EQ_OP);
		break;
	case NE_OP:
		Match(NE_OP);
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::CondTail()
{
	ExprRec expr;
	switch (NextToken())
	{
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP:
	case NE_OP:
		RelOp();
		// code.ProcessOp();
		Expression(expr);
		break;
	case RBANANA:
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::FloatListTail(ExprRec & exprRec)
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Match(FLOAT_LIT);
		code.FloatAppend(exprRec);
		FloatListTail(exprRec);
		break;
	case RSTAPLE:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}
void Parser::FloatList(ExprRec & exprRec)
{
	Match(FLOAT_LIT);
	code.FloatAppend(exprRec);
	FloatListTail(exprRec);
}

void Parser::IntListTail(ExprRec & exprRec)
{
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Match(INT_LIT);
		code.IntAppend(exprRec);
		IntListTail(exprRec);
		break;
	case RSTAPLE:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::IntList(ExprRec & exprRec)
{
	Match(INT_LIT);
	code.IntAppend(exprRec);
	IntListTail(exprRec);
}

void Parser::ForAssign()
{
	ExprRec expr;
	Variable(expr);
	Match(ASSIGN_OP);
	Expression(expr);
	// code.ForAssign();
}

void Parser::ElseClause()
{
	switch (NextToken())
	{
	case ELSE_SYM:
		Match(ELSE_SYM);
		// code.ProcessElse();
		StmtList();
		break;
	case ENDSTMT_SYM:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Condition()
{
	ExprRec expr;
	Expression(expr);
	CondTail();
	// code.SetCondition();
}

void Parser::ForStmt()
{
	Match(FOR_SYM);
	Match(LBANANA);
	ForAssign();
	Match(SEMICOLON);
	Condition();
	Match(SEMICOLON);
	// code.ForUpdate();
	ForAssign();
	Match(RBANANA);
	StmtList();
	Match(ENDSTMT_SYM);
	// code.ForEnd();
}

void Parser::DoStmt()
{
	Match(DO_SYM);
	// code.DoLoopBegin();
	StmtList();
	Match(UNTIL_SYM);
	Match(LBANANA);
	Condition();
	Match(RBANANA);
	// code.DoLoopEnd();
	Match(SEMICOLON);
}

void Parser::WhileStmt()
{
	Match(WHILE_SYM);
	Match(LBANANA);
	Condition();
	Match(RBANANA);
	// code.WhileBegin();
	StmtList();
	Match(ENDSTMT_SYM);
	// code.WhileEnd();
}

void Parser::IfStmt()
{
	Match(IF_SYM);
	Match(LBANANA);
	Condition();
	Match(RBANANA);
	// code.ProcessIf();
	StmtList();
	ElseClause();
	Match(ENDSTMT_SYM);
	// code.IfEnd();
}

void Parser::ItemListTail()
{
	ExprRec expr;
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Expression(expr);
		code.WriteExpr(expr);
		ItemListTail();
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::ItemList()
{
	ExprRec expr;
	Expression(expr);
	code.WriteExpr(expr);
	ItemListTail();
}

void Parser::VariableTail(ExprRec & expr)
{
	switch (NextToken())
	{
	case LSTAPLE:
		Match(LSTAPLE);
		Expression(expr);
		Match(RSTAPLE);
		break;
	case RSTAPLE:
	case RBANANA:
	case SEMICOLON:
	case COMMA:
	case ASSIGN_OP:
	case PLUS_OP:
	case MINUS_OP:
	case MULT_OP:
	case REALDIV_OP:
	case INTEGERDIV_OP:
	case LT_OP:
	case LE_OP:
	case GT_OP:
	case GE_OP:
	case EQ_OP:
	case NE_OP:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarListTail()
{
	ExprRec expr;
	switch (NextToken())
	{
	case COMMA:
		Match(COMMA);
		Variable(expr);
		code.InputVar(expr);
		VarListTail();
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::VarList()
{
	ExprRec identifier;
	Variable(identifier);
	code.InputVar(identifier);
	VarListTail();
}

void Parser::Expression(ExprRec& expr)
{
	Factor(expr);
	ExprTail(expr);
}

void Parser::Variable(ExprRec& identifer)
{
	Match(ID);
	identifer.name = scan.tokenBuffer;
	VariableTail(identifer);
	code.ProcessVar(identifer);
}

void Parser::BreakStmt()
{
	Match(BREAK_SYM);
	// code.Break();
	Match(SEMICOLON);
}

void Parser::NewlineStmt()
{
	Match(NEWLINE_SYM);
	code.NewLine();
	Match(SEMICOLON);
}

void Parser::OutputStmt()
{
	Match(OUTPUT_SYM);
	ItemList();
	Match(SEMICOLON);
}

void Parser::InputStmt()
{
	Match(INPUT_SYM);
	VarList();
	Match(SEMICOLON);
}

void Parser::AssignStmt()
{
	ExprRec expr, result;
	Variable(expr);
	Match(ASSIGN_OP);
	Expression(result);
	code.Assign(expr, result);
	Match(SEMICOLON);
}

void Parser::StructStmt()
{
	switch (NextToken())
	{
	case IF_SYM:
		IfStmt();
		break;
	case WHILE_SYM:
		WhileStmt();
		break;
	case DO_SYM:
		DoStmt();
		break;
	case FOR_SYM:
		ForStmt();
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::SimpleStmt()
{
	switch (NextToken())
	{
	case ID:
		AssignStmt();
		break;
	case INPUT_SYM:
		InputStmt();
		break;
	case OUTPUT_SYM:
		OutputStmt();
		break;
	case NEWLINE_SYM:
		NewlineStmt();
		break;
	case BREAK_SYM:
		BreakStmt();
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::StmtTail()
{
	switch (NextToken())
	{
	case BREAK_SYM:
	case DO_SYM:
	case FOR_SYM:
	case INPUT_SYM:
	case NEWLINE_SYM:
	case OUTPUT_SYM:
	case WHILE_SYM:
	case IF_SYM:
	case ID:
		Statement();
		StmtTail();
		break;
	case UNTIL_SYM:
	case END_SYM:
	case ELSE_SYM:
	case ENDSTMT_SYM:
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::Statement()
{
	switch (NextToken())
	{
	case BREAK_SYM:
	case INPUT_SYM:
	case NEWLINE_SYM:
	case OUTPUT_SYM:
	case ID:
		SimpleStmt();
		break;
	case DO_SYM:
	case FOR_SYM:
	case WHILE_SYM:
	case IF_SYM:
		StructStmt();
		break;
	default:
		SyntaxError(NextToken(), "");
	}
}

void Parser::StmtList()
{
	Statement();
	StmtTail();
}

void Parser::DecList()
{
	Declaration();
	DecTail();
}

void Parser::Program()
{
	Match(BEGIN_SYM);
	code.Start();
	DecList();
	StmtList();
	Match(END_SYM);
	code.Finish();
}

void Parser::SystemGoal()
{
	Program();
	Match(EOF_SYM);
}
