#include "scan.h"
#include "defs.h"
#include <stdio.h>
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

static void scanfile()
{
	struct token t;

	while (scan(&t)) {
		printf("Token %s", tokstr[t.token]);
		if (t.token == T_INTLIT)
			printf(", value %d", t.intvalue);
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		usage(argv[0]);

	init();
	Infile = fopen(argv[1], "r");
	scanfile();
	return 0;
}