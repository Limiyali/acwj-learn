#include "expr.h"
#include "data.h"
#include "scan.h"
#include <stdio.h>

int arithop(int t)
{
	switch (t) {
	case T_PLUS:
		return A_ADD;
	case T_MINUS:
		return A_SUBTRACT;
	case T_STAR:
		return A_MULTIPLY;
	case T_SLASH:
		return A_DIVIDE;
	default:
		fprintf(stderr, "syntax error on line %d, token %d\n", Line, t);
		exit(1);
	}
}

static struct ASTnode *primary(void)
{
	struct ASTnode *n;

	switch (Token.token) {
	case T_INTLIT:
		n = mkastleaf(A_INTLIT, Token.intvalue);
		scan(&Token);
		return n;

	default:
		fprintf(stderr, "syntax error on line %d, token %d\n", Line,
				Token.token);
		exit(1);
	}
}

struct ASTnode *binexpr(void)
{
	struct ASTnode *n, *left, *right;
	int nodetype;

	left = primary();
	if (Token.token == T_EOF)
		return left;
	nodetype = arithop(Token.token);
	scan(&Token);
	right = binexpr();
	n = mkastnode(nodetype, left, right, 0);
	return n;
}

struct ASTnode *additive_expr(void)
{
	struct ASTnode *left, *right;
	int tokentype;

	// Get the left sub-tree at a higher precedence than us
	left = multiplicative_expr();

	// If no tokens left, return just the left node
	tokentype = Token.token;
	if (tokentype == T_EOF)
		return (left);

	// Loop working on token at our level of precedence
	while (1) {
		// Fetch in the next integer literal
		scan(&Token);

		// Get the right sub-tree at a higher precedence than us
		right = multiplicative_expr();

		// Join the two sub-trees with our low-precedence operator
		left = mkastnode(arithop(tokentype), left, right, 0);

		// And get the next token at our precedence
		tokentype = Token.token;
		if (tokentype == T_EOF)
			break;
	}

	// Return whatever tree we have created
	return (left);
}

struct ASTnode *multiplicative_expr(void)
{
	struct ASTnode *left, *right;
	int tokentype;

	// Get the integer literal on the left.
	// Fetch the next token at the same time.
	left = primary();

	// If no tokens left, return just the left node
	tokentype = Token.token;
	if (tokentype == T_EOF)
		return (left);
	arithop(tokentype);

	// While the token is a '*' or '/'
	while ((tokentype == T_STAR) || (tokentype == T_SLASH)) {
		// Fetch in the next integer literal
		scan(&Token);
		right = primary();

		// Join that with the left integer literal
		left = mkastnode(arithop(tokentype), left, right, 0);

		// Update the details of the current token.
		// If no tokens left, return just the left node
		tokentype = Token.token;
		if (tokentype == T_EOF)
			break;
	}

	// Return whatever tree we have created
	return (left);
}