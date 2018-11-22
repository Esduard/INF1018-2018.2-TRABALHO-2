#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef int (*funcp) (int x);

static void error (const char *msg, int line);

void gera_codigo (FILE *f, void **code, funcp *entry);


void libera_codigo (void *p);
