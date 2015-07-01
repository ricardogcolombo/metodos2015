#ifndef _BICUBIC_H
#define _BICUBIC_H

#include "common.h"

using namespace std;
using namespace cv;


struct valoresSpline {
	double *as;
	double *bs;
	double *cs;
	double *ds;
};

void bicubic(Mat *image, Mat* imageRes, int k);

#endif
