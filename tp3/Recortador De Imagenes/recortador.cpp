#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/gpu/gpu.hpp>        // GPU structures and methods

using namespace cv;
using namespace std;

double getPSNR(Mat *I1, Mat *I2, int k);
void vecinos(Mat *image, Mat *imageRes, int k);
void dividirEnVentanas(Mat *image, Mat *imageRes, int k);
void copy(Mat *dest, Mat *src, int fila, int columna);

int main( int argc, char** argv ) {
	if ( argc != 5) {
		std::cout << " Usage: archivoEntrada archivoComparativo archivoResaizeado k" << std::endl;
		return -1;
	}

	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
	int k = atoi(argv[3]);
	if (! image.data ) {                           // Check for invalid input
		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}

	int cantidadFilas = 0;
	for (int i = 0; i < image.rows; i += k)
		cantidadFilas++;

	int cantidadCols = 0;
	for (int i = 0; i < image.cols; i += k)
		cantidadCols++;
	Mat imageRes(cantidadFilas, cantidadCols, DataType<uchar>::type);
	Mat imageComp(cantidadFilas*k, cantidadCols*k, DataType<uchar>::type);

	for (int i = 0; i < cantidadFilas*k; i++)
		for (int j = 0; j < cantidadCols*k; j++){
			imageComp.at<uchar>(i, j) = image.at<uchar>(i,j);
		}


	for (int i = 0; i < cantidadFilas; i++)
		for (int j = 0; j < cantidadCols; j++){
			imageRes.at<uchar>(i, j) = image.at<uchar>(i*k,j*k);
		}
	imwrite( argv[3], imageRes );
	imwrite( argv[2], imageComp );
	return 0;
}