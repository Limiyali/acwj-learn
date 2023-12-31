#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

struct ASTnode *mkastnode(int op, int type, struct ASTnode *left,
						  struct ASTnode *mid, struct ASTnode *right,
						  int intvalue)
{
	struct ASTnode *n;
	n = malloc(sizeof(struct ASTnode));
	if (!n) {
		fprintf(stderr, "Unable to malloc in mkastnode()\n");
		exit(1);
	}
	n->op = op;
	n->left = left;
	n->mid = mid;
	n->right = right;
	n->type = type;
	n->v.intvalue = intvalue;
	return n;
}

struct ASTnode *mkastleaf(int op, int type, int intvalue)
{
	return mkastnode(op, type, NULL, NULL, NULL, intvalue);
}

struct ASTnode *mkastunary(int op, int type, struct ASTnode *left, int intvalue)
{
	return mkastnode(op, type, left, NULL, NULL, intvalue);
}