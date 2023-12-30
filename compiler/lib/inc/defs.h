#pragma once

struct token {
	int token;
	int intvalue;
};

struct symtable {
	char *name; // Name of a symbol
};

enum {
	T_EOF,
	T_PLUS,
	T_MINUS,
	T_STAR,
	T_SLASH,
	T_INTLIT,
	T_SEMI,
	T_PRINT,
	T_INT,
	T_EQUALS,
	T_IDENT
};

enum {
	A_ADD,
	A_SUBTRACT,
	A_MULTIPLY,
	A_DIVIDE,
	A_INTLIT,
	A_LVIDENT,
	A_ASSIGN,
	A_IDENT
};

struct ASTnode {
	int op;
	struct ASTnode *left;
	struct ASTnode *right;
	union defs {
		int intvalue;
		int id;
	} v;
};
