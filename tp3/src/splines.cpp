#include "splines.h"
valoresSpline calcularSplines(Mat *image, int fila, int k);

void bicubic(Mat *image, Mat *imageRes, int k) {
	for(int t = 0; t < image->rows;t++)
	{	
		for(int i = 0; i < image->cols;i++)
		{
			valoresSpline spline = calcularSplines(image,t,k);
			for(int j = 0; j < k;j++){
				//polinomio
				int valor = spline.as[j]+spline.bs[j]*j+spline.cs[j]*j*j+spline.cs[j]*j*j*j;
				imageRes->at<uchar>((i*k)+j, t) = valor;
			}
		}
	}

	Mat imageRes2 =imageRes->t();

	for(int t = 0; t < imageRes->rows;t++)
	{	
		for(int i = 0; i < image->cols;i++)
		{
			valoresSpline spline = calcularSplines(&imageRes2,t,k);
			for(int j = 0; j < k;j++){
				//polinomio
				int valor = spline.as[j]+spline.bs[j]*j+spline.cs[j]*j*j+spline.cs[j]*j*j*j;
				imageRes2.at<uchar>(j, i*k ) = valor;
			}
		}
	}
	
    imshow( "Display window",imageRes2 );                   // Show our image inside it.
}

valoresSpline calcularSplines(Mat *image, int fila, int k)
{
	MatrizB *MatrizSpline = new MatrizB(image->cols, 1);
	double *b = new double[image->cols];
	MatrizSpline->setVal(0, 0, 1);
	b[0] = 0;
	for(int i = 1; i < image->cols-1; i++) {
		MatrizSpline->setVal(i-1, i, k);
		MatrizSpline->setVal(i, i, 4*k);
		MatrizSpline->setVal(i+1, i, k);
		b[i] = (3/k)*(image->at<uchar>(i+2, fila)-2*image->at<uchar>(i+1, fila)+image->at<uchar>(i, fila));
	}
	MatrizSpline->setVal(image->cols-1, image->cols-1, 1);
	b[image->cols-1] = 0;
	gauss(MatrizSpline,b);
	double *cs = backward_substitution(MatrizSpline, b);
	
	double *bs = new double[image->cols];
	for(int i = 0; i < image->cols-1; i++)
	{
		bs[i] = (1/k)*(image->at<uchar>(i+1, 1)-image->at<uchar>(i, fila))-(k/3)*(2*cs[i]+cs[i+1]);
	}
	
	double *as = new double[image->cols];
	for(int i = 0; i < image->cols-1; i++)
	{
		as[i] = image->at<uchar>(i, fila);
	}

	double *ds = new double[image->cols];
	for(int i = 0; i < image->cols-1; i++)
	{
		ds[i] = (cs[i+1] - cs[i] )/(3*k) ;
	}	
	
	valoresSpline resultado;
	resultado.as = as;
	resultado.bs = bs;
	resultado.cs = cs;
	resultado.ds = ds;
	return resultado;
}
