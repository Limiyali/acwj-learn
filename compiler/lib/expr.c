#include "expr.h"
#include "data.h"
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
		fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
		exit(1);
	}
}