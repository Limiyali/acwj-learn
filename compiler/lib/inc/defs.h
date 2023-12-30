#pragma once

struct token {
	int token;
	int intvalue;
};

enum { T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_PRINT };

enum { A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT };

struct ASTnode {
	int op;
	struct ASTnode *left;
	struct ASTnode *right;
	int intvalue;
};
