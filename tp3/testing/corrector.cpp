#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/gpu/gpu.hpp>        // GPU structures and methods
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

double errorCuadraticoMedio(Mat* im1, Mat *im2);
double getPSNR(Mat *I1, Mat *I2);

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Modo de uso: corrector imagen1.png imagen2.png archivoDeSalida.txt" << endl;
		return -1;
	}
	Mat imagen1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat imagen2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	if (! imagen1.data ) {                           // Check for invalid input
		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}

	if (! imagen2.data ) {                           // Check for invalid input
		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	double errorC = errorCuadraticoMedio(&imagen1, &imagen2);

	double psnr = getPSNR(&imagen1, &imagen2);
	cout << errorC << " " << psnr << endl;;
	return 0;
}

//COMO FUNCIONA?
double getPSNR(Mat *I1, Mat *I2) {
	long unsigned int res = 0;
	for (int i = 0; i < I1->rows; i++) {
		for (int j = 0; j < I1->cols; j++) {
			res += (I1->at<uchar>(i, j) - I2->at<uchar>(i, j)) * (I1->at<uchar>(i, j) - I2->at<uchar>(i, j));
		}
	}
	double mse  = res/(double)(I1->rows * I1->cols);
	double psnr = 10.0 * log10((255 * 255) / mse);
	return psnr;
}


double errorCuadraticoMedio(Mat* im1, Mat *im2) {
	unsigned long int aux = 0;
	for (int i = 0; i < im1->rows; i++)
		for (int j = 0; j < im1->cols; j++) {
			aux += (im1->at<uchar>(i, j) - im2->at<uchar>(i, j)) * (im1->at<uchar>(i, j) - im2->at<uchar>(i, j));
		}
	double resultado = aux / (double)(im1->rows * im1->cols);
	return resultado;
}
