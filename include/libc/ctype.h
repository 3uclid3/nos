#pragma once

#include <stddef.h>

BEGIN_C_DECLS

int isalnum(int c);
int isalpha(int c);
int islower(int c);
int isupper(int c);
int isdigit(int c);
int isxdigit(int c);
int iscntrl(int c);
int isgraph(int c);
int isspace(int c);
int isblank(int c);
int isprint(int c);
int ispunct(int c);
int toupper(int c);
int tolower(int c);

END_C_DECLS
