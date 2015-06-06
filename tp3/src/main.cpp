#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/gpu/gpu.hpp>        // GPU structures and methods
//#include <string>   // for strings
//#include <iomanip>  // for controlling float print precision
//#include <sstream>  // string to number conversion

using namespace cv;
using namespace std;

double getPSNR(const Mat& I1, const Mat& I2);

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file


    if(! image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	
	int k=2;
	Mat imageRes(((image.rows-1)*(k+1))+1, ((image.cols-1)*(k+1))+1, DataType<uchar>::type);
		
	
	for(int i=0; i<image.rows; i++){
		for(int j=0; j<image.cols; j++){

			//cout << "I es: " << i << endl;
			//cout << "J es: " << j << endl;			

			int m = i*(k+1);
			int l = j*(k+1);			
			int finI = (i*(k+1))+1;
			int finJ = (j*(k+1))+1;

			// Proceso el último pixel
			if(j == image.cols-1 && i == image.rows-1){
				imageRes.at<uchar>(m,l) = image.at<uchar>(i,j);
				break;
			}

			// Proceso la última columna
			if(j == image.cols-1){
				//cout << "Estoy en la ultima columna..." << endl;
				//cout << "desde M: " << m << "  " << "hasta M: " << finI << endl;
				int finI = m+k;
				
				for(m; m<=finI; m++){
					imageRes.at<uchar>(m,l) = image.at<uchar>(i,j);
				}

				// Proceso la última fila
			}else if(i == image.rows-1){			
				//cout << "Estoy en la ultima fila..." << endl;
				//cout << "desde L: " << l << "  " << "hasta L: " << finJ << endl;

				int finJ = l+k;
				for(l; l<=finJ; l++){
					imageRes.at<uchar>(m,l) = image.at<uchar>(i,j);
				}

				// Resto de la imagen
			}else{			
					//cout << "desde M: " << m << "  " << "hasta M: " << finI << endl;
					//cout << "desde L: " << l << "  " << "hasta L: " << finJ << endl;
				
				for(int m = i*(k+1); m<=finI; m++){
					for(int l = j*(k+1); l<=finJ; l++){
						//cout << "posicion: " << i << "  " << j << endl;
						//cout << "Valor del pixel " << i << j << "es: " << image.at<uchar>(i,j) << endl;
						imageRes.at<uchar>(m,l) = image.at<uchar>(i,j);		
						//imageRes.at<uchar>(m,l) = 255.0;			
					}
				}
			}
		}
	}
	
	//cout << "termino el ciclo" << endl;

	cout << "Tamano fila imagen fuente: " << image.rows << endl;
	cout << "Tamano columna imagen fuente: " << image.cols << endl;

	cout << "Tamano fila imagen destino: " << imageRes.rows << endl;
	cout << "Tamano columna imagen destino: " << imageRes.cols << endl;

	//double res = getPSNR(imageRes, image);
	//cout << "La diferencia es: " << res << endl;

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", imageRes );                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
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