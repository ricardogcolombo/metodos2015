
#include "bilineal.h"
#include "common.h"

using namespace cv;
using namespace std;

double getPSNR(const Mat& I1, const Mat& I2);
void vecinos(Mat *image, Mat *imageRes, int k);

int main( int argc, char** argv )
{
    if( argc != 4)
    {
     std::cout <<" Usage: filename filter k" << std::endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
    int method = atoi(argv[2]);
    int k = atoi(argv[3]);
    int resRows = (image.rows-1)*k + image.rows;
    int resCols = (image.cols-1)*k + image.cols;
    Mat imageRes(resRows, resCols, DataType<uchar>::type);

    if(! image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    switch(method) {
      case 1:
        vecinos(&image, &imageRes, k);
        break;
      case 2:
        bilineal(&image, &imageRes, k);
        break;
      case 3:
        cout << "EJ3 no implementado" << endl;
        break;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", imageRes );                   // Show our image inside it.
    imwrite( "res.jpg", imageRes );


	cout << "Tamano fila imagen fuente: " << image.rows << endl;
	cout << "Tamano columna imagen fuente: " << image.cols << endl;

	cout << "Tamano fila imagen destino: " << imageRes.rows << endl;
	cout << "Tamano columna imagen destino: " << imageRes.cols << endl;

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}

void vecinos(Mat *image, Mat *imageRes, int k) { 
	for(int i=0; i<imageRes->rows; i++){
		for(int j=0; j<imageRes->cols; j++){
      imageRes->at<uchar>(i, j) = image->at<uchar>(round(i/(k+1)), round(j/(k+1)));
    }
  }
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
