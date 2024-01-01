#pragma once

int cgprimsize(int type);
void freeall_registers(void);
void cgpreamble();
void cgfuncpreamble(char *name);
void cgfuncpostamble(int id);
void cgglobsym(int id);
int cgloadint(int value, int type);
int cgloadglob(int id);
int cgadd(int r1, int r2);
int cgmul(int r1, int r2);
int cgsub(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
int cgcall(int r, int id);
int cgstorglob(int r, int id);
void cgglobsym(int id);
int cgcompare_and_set(int ASTop, int r1, int r2);
void cglabel(int l);
void cgjump(int l);
int cgcompare_and_jump(int ASTop, int r1, int r2, int label);
int cgwiden(int r, int oldtype, int newtype);
void cgreturn(int reg, int id);