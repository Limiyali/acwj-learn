#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right,
						  int intvalue)
{
	struct ASTnode *new;
	new = malloc(sizeof(struct ASTnode));
	if (!new) {
		fprintf(stderr, "Unable to malloc in mkastnode()\n");
		exit(1);
	}
	new->op = op;
	new->left = left;
	new->right = right;
	new->intvalue = intvalue;
	return new;
}

struct ASTnode *mkastleaf(int op, int intvalue)
{
	return mkastnode(op, NULL, NULL, intvalue);
}

struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue)
{
	return mkastnode(op, left, NULL, intvalue);
}