#include "sym.h"
#include "defs.h"
#include "data.h"
#include "misc.h"
#include <string.h>
#include <stdlib.h>

static int Globs = 0; // Position of next free global symbol slot

int findglob(char *s)
{
	int i;
	for (i = 0; i < Globs; i++) {
		if (*s == *Gsym[i].name && !strcmp(s, Gsym[i].name))
			return i;
	}
	return -1;
}

static int newglob(void)
{
	int p;

	if ((p = Globs++) >= NSYMBOLS)
		fatal("Too many global symbols");
	return (p);
}

int addglob(char *name, int type, int stype, int endlabel)
{
	int y;

	// If this is already in the symbol table, return the existing slot
	if ((y = findglob(name)) != -1)
		return (y);

	// Otherwise get a new slot, fill it in and
	// return the slot number
	y = newglob();
	Gsym[y].name = strdup(name);
	Gsym[y].type = type;
	Gsym[y].stype = stype;
	Gsym[y].endlabel = endlabel;
	return (y);
}