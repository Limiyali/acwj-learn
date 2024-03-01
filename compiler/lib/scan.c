#include "data.h"
#include "scan.h"
#include "defs.h"
#include "misc.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
static struct token *Rejtoken = NULL;

static int chrpos(char *s, int c)
{
	char *p;
	p = strchr(s, c);
	return (p ? p - s : -1);
}

static int next(void)
{
	int c;

	if (Putback) {
		c = Putback;
		Putback = 0;
		return c;
	}

	c = getc(Infile);
	if ('\n' == c)
		Line++;
	return c;
}

static void putback(int c)
{
	Putback = c;
}

static int skip(void)
{
	int c;
	c = next();
	while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c)
		c = next();
	return c;
}

static int scanint(int c)
{
	int k, val = 0;

	while ((k = chrpos("0123456789", c)) >= 0) {
		val = val * 10 + k;
		c = next();
	}

	putback(c);
	return val;
}

static int scanident(int c, char *buf, int lim)
{
	int i = 0;
	while (isalpha(c) || isdigit(c) || '_' == c) {
		if (lim - 1 == i) {
			printf("identifier too long on line %d\n", Line);
			exit(1);
		} else if (i < lim - 1)
			buf[i++] = c;
		c = next();
	}
	putback(c);
	buf[i] = '\0';
	return i;
}

static int keyword(char *s)
{
	switch (*s) {
	case 'e':
		if (!strcmp(s, "else"))
			return (T_ELSE);
		break;
	case 'i':
		if (!strcmp(s, "if"))
			return (T_IF);
		if (!strcmp(s, "int"))
			return (T_INT);
		break;
	case 'p':
		if (!strcmp(s, "print"))
			return (T_PRINT);
		break;
	case 'w':
		if (!strcmp(s, "while"))
			return (T_WHILE);
		break;
	case 'f':
		if (!strcmp(s, "for"))
			return (T_FOR);
		break;
	case 'v':
		if (!strcmp(s, "void"))
			return (T_VOID);
		break;
	case 'c':
		if (!strcmp(s, "char"))
			return (T_CHAR);
		break;
	case 'l':
		if (!strcmp(s, "long"))
			return (T_LONG);
		break;
	case 'r':
		if (!strcmp(s, "return"))
			return (T_RETURN);
		break;
	}
	return (0);
}

void reject_token(struct token *t)
{
	if (Rejtoken != NULL)
		fatal("Can't reject token twice");
	Rejtoken = t;
}

int scan(struct token *t)
{
	int c, tokentype;

	if (Rejtoken != NULL) {
		t = Rejtoken;
		Rejtoken = NULL;
		return 1;
	}

	// Skip whitespace
	c = skip();

	// Determine the token based on
	// the input character
	switch (c) {
	case EOF:
		t->token = T_EOF;
		return (0);
	case '+':
		t->token = T_PLUS;
		break;
	case '-':
		t->token = T_MINUS;
		break;
	case '*':
		t->token = T_STAR;
		break;
	case '/':
		t->token = T_SLASH;
		break;
	case ';':
		t->token = T_SEMI;
		break;
	case '{':
		t->token = T_LBRACE;
		break;
	case '}':
		t->token = T_RBRACE;
		break;
	case '(':
		t->token = T_LPAREN;
		break;
	case ')':
		t->token = T_RPAREN;
		break;
	case '=':
		if ((c = next()) == '=') {
			t->token = T_EQ;
		} else {
			putback(c);
			t->token = T_ASSIGN;
		}
		break;
	case '!':
		if ((c = next()) == '=') {
			t->token = T_NE;
		} else {
			fatalc("Unrecognised character", c);
		}
		break;
	case '<':
		if ((c = next()) == '=') {
			t->token = T_LE;
		} else {
			putback(c);
			t->token = T_LT;
		}
		break;
	case '>':
		if ((c = next()) == '=') {
			t->token = T_GE;
		} else {
			putback(c);
			t->token = T_GT;
		}
		break;
	case '&':
		if ((c = next()) == '&') {
			t->token = T_LOGAND;
		} else {
			putback(c);
			t->token = T_AMPER;
		}
		break;
	default:

		// If it's a digit, scan the
		// literal integer value in
		if (isdigit(c)) {
			t->intvalue = scanint(c);
			t->token = T_INTLIT;
			break;
		} else if (isalpha(c) || '_' == c) {
			// Read in a keyword or identifier
			scanident(c, Text, TEXTLEN);

			// If it's a recognised keyword, return that token
			if ((tokentype = keyword(Text))) {
				t->token = tokentype;
				break;
			}
			// Not a recognised keyword, so it must be an identifier
			t->token = T_IDENT;
			break;
		}
		// The character isn't part of any recognised token, error
		fatalc("Unrecognised character", c);
	}
	return 1;
}