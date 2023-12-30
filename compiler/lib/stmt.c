#include "stmt.h"
#include "misc.h"
#include "defs.h"
#include "tree.h"
#include "expr.h"
#include "gen.h"
#include "data.h"
#include "sym.h"

static void print_statement(void)
{
	struct ASTnode *tree;
	int reg;

	match(T_PRINT, "print");
	tree = binexpr(0);
	reg = genAST(tree, -1);
	genprintint(reg);
	genfreeregs();
	semi();
	if (Token.token == T_EOF)
		return;
}

static void var_declaration(void)
{
	match(T_INT, "int");
	ident();
	addglob(Text);
	genglobsym(Text);
	semi();
}

static void assignment_statement(void)
{
	struct ASTnode *left, *right, *tree;
	int id;

	ident();

	if ((id = findglob(Text)) == -1)
		fatals("Undeclared variable", Text);
	right = mkastleaf(A_LVIDENT, id);
	match(T_ASSIGN, "=");
	left = binexpr(0);
	tree = mkastnode(A_ASSIGN, left, right, 0);
	genAST(tree, -1);
	genfreeregs();

	semi();
}

void statements(void)
{
	while (1) {
		switch (Token.token) {
		case T_PRINT:
			print_statement();
			break;
		case T_INT:
			var_declaration();
			break;
		case T_IDENT:
			assignment_statement();
			break;
		case T_EOF:
			return;
		default:
			fatald("Syntax error, token", Token.token);
		}
	}
}