#ifndef SEM_PATCH
#define SEM_PATCH

enum struct sem : int {
	PART,
	BLOCK,
	DO_WHILE,
	ASSIGN,
	IDENT,
	NUM,
	OR,
	AND,
	EQU,
	NEQU,
	NOT,
	GT,
	LT,
	NGT,
	NLT,
	PLUS,
	MINUS,
	MUL,
	DIV
};

#endif
