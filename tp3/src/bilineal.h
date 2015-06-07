#ifndef _BILINEAL_H
#define _BILINEAL_H

#include "common.h"

typedef struct interpoladores {
  point q11;
  point q21;
  point q12;
  point q22;
} interpoladores;



void polinomioInterpolador(point *res, interpoladores *Q);
void bilineal(Mat image, Mat imageRes, int k);


#endif
