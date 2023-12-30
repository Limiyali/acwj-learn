#pragma once
#include "defs.h"
#include "tree.h"

int genAST(struct ASTnode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);