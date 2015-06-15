#include "splines.h"
valoresSpline calcularSplines(Mat *image, int fila, int k);

void bicubic(Mat *image, Mat *imageRes, int k) {
	
	for(int t = 0; t < image->rows;t++)
	{	
		valoresSpline spline = calcularSplines(image,t,k);
		for(int i = 0; i < image->cols;i++)
		{
			for(int j = 0; j < k+1;j++){
				//polinomio
				int valor = spline.as[i]+spline.bs[i]*j+spline.cs[i]*j*j+spline.ds[i]*j*j*j;
				if(valor > 255)
					valor = 255;
				if(valor < 0)
					valor = 0;
				imageRes->at<uchar>((i*(k))+j,t*(k) ) = valor;
			}
		}
		delete[] spline.as;
		delete[] spline.bs;
		delete[] spline.cs;
		delete[] spline.ds;		
	}

	// Mat imageRes2 =imageRes->t();

	// for(int t = 0; t < imageRes->rows;t++)
	// {	
	// 	valoresSpline spline = calcularSplines(image,t,k);
	// 	for(int i = 0; i < image->cols;i++)
	// 	{
	// 		for(int j = 0; j < k;j++){
	// 			//polinomio
	// 			int valor = spline.as[i]+spline.bs[i]*j+spline.cs[i]*j*j+spline.ds[i]*j*j*j;
	// 			if(valor > 255)
	// 				valor = 255;
	// 			if(valor < 0)
	// 				valor = 0;
	// 			imageRes2.at<uchar>(t*(k+1), (i*(k+1))+j) = valor;
	// 		}
	// 	}
	// 	delete[] spline.as;
	// 	delete[] spline.bs;
	// 	delete[] spline.cs;
	// 	delete[] spline.ds;	
	// }
	// *imageRes = imageRes2.t();

	namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window",*imageRes );                   // Show our image inside it.
    imwrite( "res.jpg", *imageRes );
	waitKey(0);

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


	delete MatrizSpline;
	delete[] b;

	return resultado;
}
