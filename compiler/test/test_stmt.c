#include "scan.h"
#include "defs.h"
#include "expr.h"
#include "interp.h"
#include "gen.h"
#include "stmt.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define extern_
#include "data.h"
#undef extern_

static void init()
{
	Line = 1;
	Putback = '\n';
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

	if ((Infile = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	// Create the output file
	if ((Outfile = fopen("out.s", "w")) == NULL) {
		fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
		exit(1);
	}

	scan(&Token);
	genpreamble();
	struct ASTnode *tree = compound_statement();
	genAST(tree, NOREG, 0);
	genpostamble();
	fclose(Outfile);
	return 0;
}