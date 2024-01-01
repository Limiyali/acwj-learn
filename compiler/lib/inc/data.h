#include <stdlib.h>
#include <stdio.h>
#include "defs.h"

#ifndef extern_
#define extern_ extern
#endif
#define TEXTLEN 512 // Length of symbols in input
#define NSYMBOLS 1024 // Number of symbol table entries

extern_ int Line;
extern_ int Putback;
extern_ FILE *Infile;
extern_ FILE *Outfile;
extern_ struct token Token;
extern_ char Text[TEXTLEN + 1]; // Last identifier scanned
extern_ struct symtable Gsym[NSYMBOLS]; // Global symbol table
extern_ int Functionid;