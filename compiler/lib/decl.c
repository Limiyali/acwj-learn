#include "decl.h"
#include "defs.h"
#include "misc.h"
#include "tree.h"
#include "data.h"
#include "sym.h"
#include "gen.h"
#include "stmt.h"
#include "scan.h"

int parse_type(int t)
{
	if (t == T_CHAR)
		return (P_CHAR);
	if (t == T_INT)
		return (P_INT);
	if (t == T_LONG)
		return (P_LONG);
	if (t == T_VOID)
		return (P_VOID);
	fatald("Illegal type, token", t);
	return (P_VOID);
}

void var_declaration(void)
{
	int id, type;

	type = parse_type(Token.token);
	scan(&Token);
	ident();
	id = addglob(Text, type, S_VARIABLE, 0);
	genglobsym(id);
	semi();
}

struct ASTnode *function_declaration(void)
{
	struct ASTnode *tree, *finalstmt;
	int nameslot, type, endlabel;

	type = parse_type(Token.token);
	scan(&Token);
	ident();

	endlabel = genlabel();
	nameslot = addglob(Text, type, S_FUNCTION, endlabel);
	Functionid = nameslot;

	lparen();
	rparen();
	tree = compound_statement();

	if (type != P_VOID) {
		finalstmt = (tree->op == A_GLUE) ? tree->right : tree;
		if (finalstmt == NULL || finalstmt->op != A_RETURN)
			fatal("No return for function with non-void type");
	}

	return mkastunary(A_FUNCTION, type, tree, nameslot);
}