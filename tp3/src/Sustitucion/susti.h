#ifndef __Sustitucion_H_INCLUDED__   // if x.h hasn't been included yet...
#define __Sustitucion_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "../EstructuraBanda/banda.h"
double *backward_substitution(MatrizB *A, double *b);
#endif
