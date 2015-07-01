#include "ventanas.h"

void copy(Mat *dest, Mat *src, int fila, int columna);
void ventanear(Mat *image, Mat *imageRes,int  i,int j, int tamanioVentana, int k);


void dividirEnVentanas(Mat *image, Mat *imageRes, int k) {
	int tamanioVentana = TAMANIOVENTANA;
	cout << image->rows << " " << image->cols << endl;
	for (int i = 0; i < image->rows - tamanioVentana; i += tamanioVentana - 1)
		for (int j = 0; j < image->cols - tamanioVentana; j += tamanioVentana - 1) {
			ventanear(image,imageRes,i,j, tamanioVentana, k);
		}
	//Estas dos pasadas son para agarrar bien los bordes
	for (int i = 0; i < image->rows - tamanioVentana; i += tamanioVentana - 1){
		ventanear(image,imageRes,i,image->cols -tamanioVentana, tamanioVentana, k);
	}

	for (int i = 0; i < image->cols - tamanioVentana; i += tamanioVentana - 1){
		ventanear(image,imageRes,image->rows -tamanioVentana,i, tamanioVentana, k);
	}
	ventanear(image,imageRes,image->rows -tamanioVentana,image->cols -tamanioVentana, tamanioVentana, k);
}


void copy(Mat *dest, Mat *src, int fila, int columna) {
	for (int i = 0; i < src->rows; i++)
		for (int j = 0; j < src-> cols; j++ ) {
			dest->at<uchar>(fila + i, columna + j) = src->at<uchar>(i, j);
		}
}

void ventanear(Mat *image, Mat *imageRes,int  i,int j, int tamanioVentana, int k){
	Mat ventana = (*image)(Rect(j, i, tamanioVentana, tamanioVentana));
	int resRows = (ventana.rows - 1) * k + ventana.rows;
	int resCols = (ventana.cols - 1) * k + ventana.cols;
	Mat ventanaAumentada(resRows, resCols, DataType<uchar>::type);
	bicubic(&ventana, &ventanaAumentada, k);
	copy(imageRes, &ventanaAumentada, i * (k + 1), j * (k + 1));
}