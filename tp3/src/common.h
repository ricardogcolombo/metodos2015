#ifndef _COMMON_H
#define _COMMON_H

#define TAMANIOVENTANA 4

#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/gpu/gpu.hpp>        // GPU structures and methods

typedef struct point {
 int x;
 int y;
 int val;
} point;

#endif
