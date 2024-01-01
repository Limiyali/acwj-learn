#include "expr.h"
#include "data.h"
#include "scan.h"
#include "sym.h"
#include "misc.h"
#include "types.h"
#include <stdio.h>

static struct ASTnode *primary(void)
{
	struct ASTnode *n;
	int id;

	switch (Token.token) {
	case T_INTLIT:
		if ((Token.intvalue) >= 0 && (Token.intvalue < 256))
			n = mkastleaf(A_INTLIT, P_CHAR, Token.intvalue);
		else
			n = mkastleaf(A_INTLIT, P_INT, Token.intvalue);
		break;
	case T_IDENT:
		scan(&Token);
		if (Token.token == T_LPAREN)
			return funccall();
		reject_token(&Token);

		id = findglob(Text);
		if (id == -1)
			fatals("Unknown variable", Text);
		n = mkastleaf(A_IDENT, Gsym[id].type, id);
		break;
	default:
		fatald("Syntax error, token", Token.token);
	}
	scan(&Token);
	return n;
}

int arithop(int tokentype)
{
	if (tokentype > T_EOF && tokentype < T_INTLIT)
		return (tokentype);
	fatald("Syntax error, token", tokentype);
	return T_EOF;
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
	int lefttype, righttype;
	int tokentype;

	left = primary();

	tokentype = Token.token;
	if (tokentype == T_SEMI || tokentype == T_RPAREN)
		return left;

	while (op_precedence(tokentype) > ptp) {
		scan(&Token);

		right = binexpr(OpPrec[tokentype]);
		lefttype = left->type;
		righttype = right->type;
		if (!type_compatible(&lefttype, &righttype, 0))
			fatal("Incompatible types");
		if (lefttype)
			left = mkastunary(lefttype, right->type, left, 0);
		if (righttype)
			right = mkastunary(righttype, left->type, right, 0);

		left = mkastnode(arithop(tokentype), left->type, left, NULL, right, 0);

		tokentype = Token.token;
		if (tokentype == T_SEMI || tokentype == T_RPAREN)
			return left;
	}
	return left;
}

struct ASTnode *funccall(void)
{
	struct ASTnode *tree;
	int id;

	if ((id = findglob(Text)) == -1) {
		fatals("Undeclared function", Text);
	}

	lparen();
	tree = binexpr(0);

	tree = mkastunary(A_FUNCCALL, Gsym[id].type, tree, id);
	rparen();
	return tree;
}