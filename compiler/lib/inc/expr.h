#pragma once
#include "defs.h"
#include "tree.h"

int arithop(int t);
struct ASTnode *binexpr(int ptp);
int op_precedence(int tokentype);