#pragma once

struct token {
	int token;
	int intvalue;
};

struct symtable {
	char *name; // Name of a symbol
	int type;
	int stype;
	int endlabel;
};

enum {
	T_EOF,
	T_PLUS,
	T_MINUS,
	T_STAR,
	T_SLASH,
	T_EQ,
	T_NE,
	T_LT,
	T_GT,
	T_LE,
	T_GE,
	T_INTLIT,
	T_SEMI,
	T_ASSIGN,
	T_IDENT,
	T_LBRACE,
	T_RBRACE,
	T_LPAREN,
	T_RPAREN,
	// Keywords
	T_PRINT,
	T_INT,
	T_IF,
	T_ELSE,
	T_WHILE,
	T_FOR,
	T_VOID,
	T_CHAR,
	T_LONG,
	T_RETURN,
	T_LOGAND,
	T_AMPER
};

enum {
	A_ADD = 1,
	A_SUBTRACT,
	A_MULTIPLY,
	A_DIVIDE,
	A_EQ,
	A_NE,
	A_LT,
	A_GT,
	A_LE,
	A_GE,
	A_INTLIT,
	A_IDENT,
	A_LVIDENT,
	A_ASSIGN,
	A_GLUE,
	A_IF,
	A_PRINT,
	A_WHILE,
	A_FORE,
	A_FUNCTION,
	A_WIDEN,
	A_FUNCCALL,
	A_RETURN,
	A_ADDR,
	A_DEREF
};

struct ASTnode {
	int op;
	int type;
	struct ASTnode *left;
	struct ASTnode *mid;
	struct ASTnode *right;
	union defs {
		int intvalue;
		int id;
	} v;
};

enum {
	P_NONE,
	P_VOID,
	P_CHAR,
	P_INT,
	P_LONG,
	P_VOIDPTR,
	P_CHARPTR,
	P_INTPTR,
	P_LONGPTR
};

enum { S_VARIABLE, S_FUNCTION };
