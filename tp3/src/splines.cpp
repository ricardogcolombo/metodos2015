#include "splines.h"
valoresSpline calcularSplines(int n , double * as, int k);

void bicubic(Mat *image, Mat *imageRes, int k) {

	for (int t = 0; t < image->rows - 1; t++) {

		double *as = new double[image->cols];
		for (int i = 0; i < image->cols; i++) {
			as[i] = image->at<uchar>(t, i);
		}
		valoresSpline spline = calcularSplines(image->cols, as, k);

		for (int i = 0; i < image->cols - 1; i++) {
			for (int j = 0; j <= k + 1; j++) {
				//polinomio
				int valor = spline.as[i] + spline.bs[i] * j + spline.cs[i] * j * j + spline.ds[i] * j * j * j;
				if (valor > 255) {
					valor = 255;
				}
				if (valor < 0) {
					valor = 0;
				}
				imageRes->at<uchar>(t * (k + 1) , (i * (k + 1)) + j) = valor;
			}
		}
		delete[] spline.as;
		delete[] spline.bs;
		delete[] spline.cs;
		delete[] spline.ds;
	}

	for (int t = 0; t < imageRes->cols - 1; t++) {
		double *as = new double[image->rows];
		for (int i = 0; i < image->rows; i++) {
			as[i] = imageRes->at<uchar>(i * (k + 1),t);
		}
		valoresSpline spline = calcularSplines(image->rows, as, k);
		for (int i = 0; i < image->rows - 1; i++) {
			for (int j = 0; j <= k + 1; j++) {
				//polinomio
				int valor = spline.as[i] + spline.bs[i] * j + spline.cs[i] * j * j + spline.ds[i] * j * j * j;
				if (valor > 255) {
					valor = 255;
				}
				if (valor < 0) {
					valor = 0;
				}
				imageRes->at<uchar>((i * (k + 1)) + j, t) = valor;
			}
		}
		delete[] spline.as;
		delete[] spline.bs;
		delete[] spline.cs;
		delete[] spline.ds;
	}






	namedWindow( "Display window", WINDOW_AUTOSIZE );
	imshow( "Display window", *imageRes );                  // Show our image inside it.
	imwrite( "res.jpg", *imageRes );
	waitKey(0);

}

//Algoritmo sacado del burden 9na edicion pagina 150
valoresSpline calcularSplines(int n , double * as, int k) {
	double *alfa = new double[n];
	for (int i = 1; i < n - 1; i++) {
		alfa[i] = (3 / k) * (as[i + 1] - as[i]) - (3 / k) * (as[i] - as[i - 1]);
	}
	double *l = new double[n];
	double *mu = new double[n];
	double *z = new double[n];
	l[0] = 1;
	mu[0] = 0;
	z[0] = 0;
	for (int i = 1; i < n - 1; i++) {
		l[i] = 2 * (2 * k) - k * mu[i - 1];
		mu[i] = k / l[i];
		z[i] = alfa[i] - (k * z[i - 1]) / l[i];
	}
	l[n - 1] = 1;
	z[n - 1] = 0;
	//Calculo los valores
	double *cs = new double[n];
	double *bs = new double[n];
	double *ds = new double[n];
	cs[n - 1] = 0;
	for (int i = n - 2; i >= 0; i--) {
		cs[i] = z[i] - mu[i] * cs[i + 1];
		bs[i] = (as[i + 1] - as[i]) / k - k * (cs[i + 1] + 2 * cs[i]) / 3;
		ds[i] = (cs[i + 1] - cs[i]) / (3 * k);
	}
	valoresSpline resultado;
	resultado.as = as;
	resultado.bs = bs;
	resultado.cs = cs;
	resultado.ds = ds;
	delete[] z;
	delete[] mu;
	delete[] l;
	delete[] alfa;
	return resultado;
}