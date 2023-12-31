#include "decl.h"
#include "defs.h"
#include "misc.h"
#include "tree.h"
#include "data.h"
#include "sym.h"
#include "stmt.h"

struct ASTnode *function_declaration(void)
{
	struct ASTnode *tree;
	int nameslot;

	match(T_VOID, "void");
	ident();
	nameslot = addglob(Text);
	lparen();
	rparen();
	tree = compound_statement();
	return mkastunary(A_FUNCTION, tree, nameslot);
}