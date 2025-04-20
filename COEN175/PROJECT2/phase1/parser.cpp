/*
 * File:	parser.cpp (lextest edition)
 *
 * Description:	This file, as is, allows you to test your updated lexer
 *		(that returns tokens) against the examples from phase 1.
 *
 */

#include <iostream>
#include "tokens.h"
#include "lexer.h"

using namespace std;

string lexbuf;
int lookahead = lexan(lexbuf);
void E();
void T();
void F();

void expression();
void ands();
void equality();
void comparison();
void additive();
void multiplicative();
void unary();
void primaryExpr(bool gobbled);
void postfixExpr(bool gobbled);
void prefix();
bool isSpecifier();
void specifier();
void pointers();
void expressionList();
void primary(bool gobbled);
void E();
void T();
void F();

void match(int t)
{
	if (lookahead == t)
		lookahead = lexan(lexbuf);
	else
		report("syntax error");
}

void expression()
{
	ands();
	while (lookahead == OR)
	{
		int op = lookahead;
		match(lookahead);
		ands();
		if (op == OR)
		{
			cout << "or" << endl;
		}
	}
}

void ands()
{
	equality();
	while (lookahead == AND)
	{
		int op = lookahead;
		match(lookahead);
		equality();
		if (op == AND)
		{
			cout << "and" << endl;
		}
	}
}

void equality()
{
	comparison();
	while (lookahead == EQL || lookahead == NEQ)
	{
		int op = lookahead;
		match(lookahead);
		comparison();
		if (op == EQL)
		{
			cout << "eq" << endl;
		}
		else
		{
			cout << "ne" << endl;
		}
	}
}

void comparison()
{
	additive();
	while (lookahead == LTN || lookahead == LEQ || lookahead == GTN || lookahead == GEQ)
	{
		int op = lookahead;
		match(lookahead);
		additive();
		if (op == LTN)
		{
			cout << "lt" << endl;
		}
		else if (op == LEQ)
		{
			cout << "le" << endl;
		}
		else if (op == GTN)
		{
			cout << "gt" << endl;
		}
		else
		{
			cout << "ge" << endl;
		}
	}
}

void additive()
{
	multiplicative();
	while (lookahead == '+' || lookahead == '-')
	{
		int op = lookahead;
		match(lookahead);
		T();
		if (op == '+')
		{
			cout << "add" << endl;
		}
		else
		{
			cout << "sub" << endl;
		}
	}
}

void multiplicative()
{
	prefix();
	while (lookahead == '*' || lookahead == '/')
	{
		int op = lookahead;
		match(lookahead);
		prefix();
		if (op == '*')
		{
			cout << "mul" << endl;
		}
		else if (op == '/')
		{
			cout << "div" << endl;
		}
		else
		{
			;
		}
	}
}

void prefix()
{
	if (lookahead == '!' || lookahead == '-' || lookahead == '*' || lookahead == '&')
	{
		int op = lookahead;
		match(lookahead);
		prefix();
		if (op == '!')
		{
			cout << "not" << endl;
		}
		else if (op == '-')
		{
			cout << "neg" << endl;
		}
		else if (op == '*')
		{
			cout << "deref" << endl;
		}
		else if (op == '&')
		{
			cout << "addr" << endl;
		}
	}
	else if (lookahead == SIZEOF)
	{
		match(lookahead);
		if (lookahead == '(')
		{
			match('(');
			if (isSpecifier())
			{
				specifier();
				pointers();
				match(')');
			}
			else
			{
				postfixExpr(true);
			}
		}
		else
			prefix();

		cout << "sizeof" << endl;
	}
	else if (lookahead == '(')
	{
		match(lookahead);
		if (isSpecifier())
		{
			specifier();
			pointers();
			match(')');
			prefix();
			cout << "cast" << endl;
		}
		else
			postfixExpr(true);
	}
	else
	{
		postfixExpr(false);
	}
}

bool isSpecifier()
{
	return (lookahead == INT || lookahead == CHAR);
}

void specifier()
{
	if (isSpecifier())
	{
		match(lookahead);
	}
	else
	{
		report("syntax error");
	}
}

void pointers()
{
	while (lookahead == '*')
	{
		match(lookahead);
	}
	return;
}

void expressionList()
{
	;
}

void postfixExpr(bool gobbled)
{
	primaryExpr(gobbled);
	while (lookahead == '[' || lookahead == '(')
	{
		int op = lookahead;
		match(lookahead);
		expression();
		if (op == '[')
		{
			match(']');
		}
		else
		{
			if (lookahead == ')')
			{
				match(')');
			}
			else
			{
				expressionList();
				match(')');
			}
		}
	}
}

void primaryExpr(bool gobbled)
{
	cout << gobbled << endl;
	if (gobbled)
	{
		expression();
		match(')');
	}
	else
	{
		if (lookahead == ID || lookahead == NUM || lookahead == CHARACTER || lookahead == STRING)
		{
			match(lookahead);
		}
		else
		{
			/* nothing to do */
		}
	}
}

void primary(bool gobbled)
{
}

void E()
{
	T();
	while (lookahead == '+' || lookahead == '-')
	{
		int op = lookahead;
		match(lookahead);
		T();
		if (op == '+')
		{
			cout << "add" << endl;
		}
		else
		{
			cout << "sub" << endl;
		}
	}
}

void T()
{
	F();
	while (lookahead == '*' || lookahead == '/')
	{
		int op = lookahead;
		match(lookahead);
		F();
		if (op == '*')
		{
			cout << "mul" << endl;
		}
		else
		{
			cout << "div" << endl;
		}
	}
}

void F()
{
	if (lookahead == '-')
	{
		match('-');
		F();
		cout << "neg" << endl;
	}
	else if (lookahead == '(')
	{
		match('(');
		E();
		match(')');
	}
	else if (lookahead == NUM || lookahead == ID)
	{
		match(lookahead);
	}
	else
		/* nothing to do */;
}

int main()
{
	lookahead = lexan(lexbuf);
	while (lookahead != DONE)
	{
		expression(); // call your top-level expression function (E for now)
		match(';');	  // match semicolon (just for this week)
	}

	cout << lineno - 1 << endl;
}

// (a>b+c) * (1234 - a[b] || c && d);
