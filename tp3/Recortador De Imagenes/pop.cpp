#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/gpu/gpu.hpp>        // GPU structures and methods

using namespace cv;
using namespace std;

int main( int argc, char** argv ) {
	if ( argc != 2) {
		std::cout << " Usage: archivoEntrada archivoComparativo archivoResaizeado k" << std::endl;
		return -1;
	}

	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
	if (! image.data ) {                           // Check for invalid input
		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	Mat imageRes(image.rows*4, image.cols*4, DataType<uchar>::type);
	resize(image, imageRes, imageRes.size(), 0, 0, INTER_CUBIC);
	imwrite( "res.png", imageRes );
	return 0;
}