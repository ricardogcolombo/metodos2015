#include "bilineal.h"

using namespace cv;
using namespace std;

void bilineal(Mat *image, Mat *imageRes, int k) {
  point *actual = (point *) malloc(sizeof(point));
  interpoladores *Q = (interpoladores *) malloc(sizeof(interpoladores));
	for(int i=0; i<image->rows-1; i++){
		for(int j=0; j<image->cols-1; j++){
      Q->q11 = (point) {.x=i*(k+1), .y=j*(k+1), .val=image->at<uchar>(i, j)};
      Q->q12 =  (point) {.x=i*(k+1), .y=j*(k+1)+k, .val=image->at<uchar>(i, j+1)};
      Q->q21 =  (point) {.x=i*(k+1)+k, .y=j*(k+1), .val=image->at<uchar>(i+1, j)};
      Q->q22 =  (point) {.x=j*(k+1)+k, .y=j*(k+1)+k, .val=image->at<uchar>(i+1, j+1)};

      for(int x = i*(k+1); x <= i*(k+1) + k; x++) {
        for(int y = j*(k+1); y <= j*(k+1) + k; y++) {
          actual->x = x;
          actual->y = y;
          actual->val = 0;     
          polinomioInterpolador(actual, Q);
          imageRes->at<uchar>(x, y) = actual->val;
        }
      }
    }
  }
  free(actual);
  free(Q);
}

void polinomioInterpolador(point *res, interpoladores *Q) {
  double denominador = (Q->q22.x - Q->q11.x) * (Q->q22.y - Q->q11.y);
  denominador = 1 / denominador;

  double numerador = Q->q11.val * (Q->q22.x - res->x) * (Q->q22.y - res->y) +
                     Q->q21.val * (res->x - Q->q11.x ) * (Q->q22.y - res->y) +
                     Q->q12.val * (Q->q22.x - res->x) * (res->y - Q->q11.y) +
                     Q->q22.val * (res->x - Q->q11.x) * (res->y - Q->q11.y);

  int out = round(numerador * denominador);
  if(out > 255) out = 255;
  if(out < 0) out = 0;
  res->val = out;
}
