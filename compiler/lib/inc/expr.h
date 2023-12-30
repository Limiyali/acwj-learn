#pragma once
#include "defs.h"
#include "tree.h"

int arithop(int t);
struct ASTnode *binexpr(void);
struct ASTnode *additive_expr(void);
struct ASTnode *multiplicative_expr(void);