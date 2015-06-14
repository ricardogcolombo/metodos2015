#ifndef _BICUBIC_H
#define _BICUBIC_H

#include "common.h"
#include "EstructuraBanda/banda.h"
#include "EliminacionGauss/ElimGauss.h"
#include "Sustitucion/susti.h"


using namespace std;
using namespace cv;


struct valoresSpline{
	double *as;
	double *bs;
	double *cs;
	double *ds;
};

void bicubic(Mat *image, Mat* imageRes, int k);

#endif
