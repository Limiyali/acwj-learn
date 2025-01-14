#include "misc.h"
#include "data.h"
#include "defs.h"
#include "scan.h"
#include <stdio.h>

void match(int t, char *what)
{
	if (Token.token == t)
		scan(&Token);
	else {
		printf("%s expected on line %d\n", what, Line);
		exit(1);
	}
}

void semi(void)
{
	match(T_SEMI, ";");
}

void lbrace()
{
	match(T_LBRACE, "{");
}

void rbrace()
{
	match(T_RBRACE, "}");
}

void lparen()
{
	match(T_LPAREN, "(");
}
void rparen()
{
	match(T_RPAREN, ")");
}

void ident(void)
{
	match(T_IDENT, "identifier");
}

void fatal(char *s)
{
	fprintf(stderr, "%s on line %d\n", s, Line);
	exit(1);
}

void fatals(char *s1, char *s2)
{
	fprintf(stderr, "%s:%s on line %d\n", s1, s2, Line);
	exit(1);
}

void fatald(char *s, int d)
{
	fprintf(stderr, "%s:%d on line %d\n", s, d, Line);
	exit(1);
}

void fatalc(char *s, int c)
{
	fprintf(stderr, "%s:%c on line %d\n", s, c, Line);
	exit(1);
}