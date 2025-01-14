#pragma once
#include "defs.h"
#include "tree.h"

#define NOREG -1

int genlabel(void);
int genAST(struct ASTnode *n, int reg, int parentASTop);
void genpreamble();
void genfreeregs();
void genprintint(int reg);
void genglobsym(int id);
int genlabel(void);
int genprimsize(int type);