#pragma once

void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgloadint(int value);
int cgloadglob(char *identifier);
int cgadd(int r1, int r2);
int cgmul(int r1, int r2);
int cgsub(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
int cgstorglob(int r, char *identifier);
void cgglobsym(char *sym);
int cgcompare_and_set(int ASTop, int r1, int r2);
void cglabel(int l);
void cgjump(int l);
int cgcompare_and_jump(int ASTop, int r1, int r2, int label);