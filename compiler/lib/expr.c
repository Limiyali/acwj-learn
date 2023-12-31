#include "expr.h"
#include "data.h"
#include "scan.h"
#include "sym.h"
#include "misc.h"
#include <stdio.h>

int arithop(int t)
{
	if (t > T_EOF && t < T_INTLIT)
		return t;
	fatald("Syntax error, token", t);
	return -1;
}

static struct ASTnode *primary(void)
{
	struct ASTnode *n;
	int id;

	switch (Token.token) {
	case T_INTLIT:
		n = mkastleaf(A_INTLIT, Token.intvalue);
		break;
	case T_IDENT:
		id = findglob(Text);
		if (id == -1)
			fatals("Unknown variable", Text);
		n = mkastleaf(A_IDENT, id);
		break;
	default:
		fatald("Syntax error, token", Token.token);
	}
	scan(&Token);
	return n;
}

static int OpPrec[] = {
	0,	10, 10, // T_EOF, T_PLUS, T_MINUS
	20, 20, // T_STAR, T_SLASH
	30, 30, // T_EQ, T_NE
	40, 40, 40, 40 // T_LT, T_GT, T_LE, T_GE
};

int op_precedence(int tokentype)
{
	int prec = OpPrec[tokentype];
	if (prec == 0) {
		fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
		exit(1);
	}
	return prec;
}

struct ASTnode *binexpr(int ptp)
{
	struct ASTnode *left, *right;
	int tokentype;

	left = primary();

	tokentype = Token.token;
	if (Token.token == T_SEMI || tokentype == T_RPAREN)
		return left;

	while (op_precedence(tokentype) > ptp) {
		scan(&Token);

		right = binexpr(OpPrec[tokentype]);
		left = mkastnode(arithop(tokentype), left, NULL, right, 0);

		tokentype = Token.token;
		if (tokentype == T_SEMI || tokentype == T_RPAREN)
			return left;
	}
	return left;
}
