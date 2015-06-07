#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/gpu/gpu.hpp>        // GPU structures and methods
#include <cmath>
//#include <string>   // for strings
//#include <iomanip>  // for controlling float print precision
//#include <sstream>  // string to number conversion

using namespace cv;
using namespace std;

double getPSNR(const Mat& I1, const Mat& I2);
void vecinos(char *filename, int k);

int main( int argc, char** argv )
{
    if( argc != 3)
    {
     std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
     return -1;
    }

    vecinos(argv[1], argv[2]);
    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}

void vecinos(char *filename, int k) {
    Mat image;
    image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return;
    }
	
  int halfK = ceil(k/2);
		
  int resRows = ((image.rows-1)*(k+1))+1;
  int resCols = ((image.cols-1)*(k+1))+1;

	Mat imageRes(resRows, resCols, DataType<uchar>::type);
	
	for(int i=0; i<image.rows; i++){
		for(int j=0; j<image.cols; j++){
      for(int l = -halfK; l<halfK;l++) {
        for(int m = -halfK; l<halfK;l++) {
          if(l >= 0 && l < resRows ) {
            if(m >= 0 && m < resCols) {
              imageRes.at<uchar>(l, m) = image.at<uchar>(i, j);
            }
          }
        }
      }
    }
  }

    //cout << "I es: " << i << endl;
    //cout << "J es: " << j << endl;			
	
	//cout << "termino el ciclo" << endl;

	cout << "Tamano fila imagen fuente: " << image.rows << endl;
	cout << "Tamano columna imagen fuente: " << image.cols << endl;

	cout << "Tamano fila imagen destino: " << imageRes.rows << endl;
	cout << "Tamano columna imagen destino: " << imageRes.cols << endl;

	//double res = getPSNR(imageRes, image);
	//cout << "La diferencia es: " << res << endl;

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", imageRes );                   // Show our image inside it.

}

/*
double getPSNR(const Mat& I1, const Mat& I2)
{
    Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    Scalar s = sum(s1);        // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // for small values return zero
        return 0;
    else
    {
        double mse  = sse / (double)(I1.channels() * I1.total());
        double psnr = 10.0 * log10((255 * 255) / mse);
        return psnr;
    }
}
*/