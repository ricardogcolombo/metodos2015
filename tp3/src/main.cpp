#include "bilineal.h"
#include "splines.h"
#include "common.h"
#include "ventanas.h"
#include <sys/time.h>

using namespace cv;
using namespace std;

double getPSNR(Mat *I1, Mat *I2, int k);
void vecinos(Mat *image, Mat *imageRes, int k);
void dividirEnVentanas(Mat *image, Mat *imageRes, int k);
void copy(Mat *dest, Mat *src, int fila, int columna);

int main( int argc, char** argv ) {
	if ( argc != 4) {
		std::cout << " Usage: filename filter k" << std::endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
	int method = atoi(argv[2]);
	int k = atoi(argv[3]);
	int resRows = (image.rows - 1) * k + image.rows;
	int resCols = (image.cols - 1) * k + image.cols;
	Mat imageRes(resRows, resCols, DataType<uchar>::type);

	if (! image.data ) {                           // Check for invalid input
		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	/*Medicion de tiempo*/
	timeval startGauss,endGauss;
	gettimeofday(&startGauss, NULL);
	/*Medicion de tiempo*/
	switch (method) {
	case 1:
		vecinos(&image, &imageRes, k);
		break;
	case 2:
		bilineal(&image, &imageRes, k);
		break;
	case 3:
		//bicubic(&image, &imageRes, k);
		dividirEnVentanas(&image, &imageRes, k);
		break;
	}
	/*Medicion de tiempo*/
	long elapsed_mtime; /* elapsed time in milliseconds */
	long elapsed_seconds; /* diff between seconds counter */
	long elapsed_useconds; /* diff between microseconds counter */
	gettimeofday(&endGauss, NULL);
	elapsed_seconds = endGauss.tv_sec - startGauss.tv_sec;
	elapsed_useconds = endGauss.tv_usec - startGauss.tv_usec;
	double tiempoExec =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
	/*Medicion de tiempo*/

	cerr << tiempoExec << endl;

	// namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
	// imshow( "Display window", imageRes );                   // Show our image inside it.
	// imwrite( "res.jpg", imageRes );


	cout << "Tamano fila imagen fuente: " << image.rows << endl;
	cout << "Tamano columna imagen fuente: " << image.cols << endl;

	cout << "Tamano fila imagen destino: " << imageRes.rows << endl;
	cout << "Tamano columna imagen destino: " << imageRes.cols << endl;

	if (k == 0) {
		double res = getPSNR(&image, &imageRes, k);
		cout << "El error PSNR es: " << res << endl;
	}

	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
}

void vecinos(Mat *image, Mat *imageRes, int k) {
	for (int i = 0; i < imageRes->rows; i++) {
		for (int j = 0; j < imageRes->cols; j++) {
			imageRes->at<uchar>(i, j) = image->at<uchar>(round(i / (k + 1)), round(j / (k + 1)));
		}
	}
}




double getPSNR(Mat *I1, Mat *I2, int k) {
	// Mat s1;
	int resRows = (I1->rows - 1) * k + I1->rows;
	int resCols = (I1->cols - 1) * k + I1->cols;
	Mat s1(resRows, resCols, DataType<double>::type);
	absdiff(*I1, *I2, s1);       // |I1 - I2|
	s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
	s1 = s1.mul(s1);           // |I1 - I2|^2

	// Scalar s = sum(s1);        // sum elements per channel

	double res = 0;

	for (int i = 0; i < s1.rows; i++) {
		for (int j = 0; j < s1.cols; j++) {
			res += s1.at<double>(i, j);
		}
	}

	// double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

	if ( res <= 1e-10) { // for small values return zero
		return 0;
	} else {
		double mse  = res / (double)(I1->rows * I1->cols);
		double psnr = 10.0 * log10((255 * 255) / mse);
		return psnr;
	}
}

