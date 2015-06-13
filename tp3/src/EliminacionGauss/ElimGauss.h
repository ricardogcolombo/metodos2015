#ifndef __MatrizB_H_INCLUDED__   
#define __MatrizB_H_INCLUDED__   

#include "../EstructuraBanda/banda.h"

MatrizB* DescompLU(MatrizB *m);
void gauss(MatrizB *m, double *b);

#endif
