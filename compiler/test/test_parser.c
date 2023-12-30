#include "scan.h"
#include "defs.h"
#include "expr.h"
#include "interp.h"
#include <stdio.h>
#define extern_
#include "data.h"
#undef extern_

static void init()
{
	Line = 1;
	Putback = '\n';
	Token.token = T_EOF;
}

static void usage(char *prog)
{
	fprintf(stderr, "Usage: %s infile\n", prog);
	exit(1);
}

char *tokstr[] = { "+", "-", "*", "/", "intlit" };

int main(int argc, char *argv[])
{
	if (argc != 2)
		usage(argv[0]);

	init();
	Infile = fopen(argv[1], "r");
	scan(&Token);
	struct ASTnode *n = binexpr(0); // Parse the expression in the file
	printf("%d\n", interpretAST(n)); // Calculate the final result
	return 0;
}