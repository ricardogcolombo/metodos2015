#include "ventanas.h"

void copy(Mat *dest, Mat *src, int fila, int columna);

void dividirEnVentanas(Mat *image, Mat *imageRes, int k) {
	int tamanioVentana = TAMANIOVENTANA;
	cout << image->rows << " " << image->cols << endl;
	for (int i = 0; i < image->rows - tamanioVentana; i += tamanioVentana - 1)
		for (int j = 0; j < image->cols - tamanioVentana; j += tamanioVentana - 1) {
			Mat ventana = (*image)(Rect(j, i, tamanioVentana, tamanioVentana));
			int resRows = (ventana.rows - 1) * k + ventana.rows;
			int resCols = (ventana.cols - 1) * k + ventana.cols;
			Mat ventanaAumentada(resRows, resCols, DataType<uchar>::type);
			bicubic(&ventana, &ventanaAumentada, k);
			copy(imageRes, &ventanaAumentada, i * (k + 1), j * (k + 1));
		}

	//Estas dos pasadas son para agarrar bien los bordes
	for (int i = 0; i < image->rows - tamanioVentana; i += tamanioVentana - 1){
		cout << i << endl;
		Mat ventana = (*image)(Rect(image->cols -tamanioVentana, i, tamanioVentana, tamanioVentana));
		int resRows = (ventana.rows - 1) * k + ventana.rows;
		int resCols = (ventana.cols - 1) * k + ventana.cols;
		Mat ventanaAumentada(resRows, resCols, DataType<uchar>::type);
		bicubic(&ventana, &ventanaAumentada, k);
		copy(imageRes, &ventanaAumentada, i * (k + 1), (image->cols - tamanioVentana) * (k + 1));
	}

	for (int i = 0; i < image->cols - tamanioVentana; i += tamanioVentana - 1){
		Mat ventana = (*image)(Rect(i,image->rows - tamanioVentana, tamanioVentana, tamanioVentana));
		int resRows = (ventana.rows - 1) * k + ventana.rows;
		int resCols = (ventana.cols - 1) * k + ventana.cols;
		Mat ventanaAumentada(resRows, resCols, DataType<uchar>::type);
		bicubic(&ventana, &ventanaAumentada, k);
		copy(imageRes, &ventanaAumentada,( image->rows - tamanioVentana)* (k + 1), i * (k + 1));
	}

	Mat ventana = (*image)(Rect(image->cols - tamanioVentana,image->rows - tamanioVentana, tamanioVentana, tamanioVentana));
	int resRows = (ventana.rows - 1) * k + ventana.rows;
	int resCols = (ventana.cols - 1) * k + ventana.cols;
	Mat ventanaAumentada(resRows, resCols, DataType<uchar>::type);
	bicubic(&ventana, &ventanaAumentada, k);
	copy(imageRes, &ventanaAumentada,( image->rows - tamanioVentana)* (k + 1),(image->cols - tamanioVentana)* (k + 1));
}


void copy(Mat *dest, Mat *src, int fila, int columna) {
	for (int i = 0; i < src->rows; i++)
		for (int j = 0; j < src-> cols; j++ ) {
			dest->at<uchar>(fila + i, columna + j) = src->at<uchar>(i, j);
		}
}