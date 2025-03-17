#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)  {

Mat image = imread(argv[1], -1);
if (image.empty()) return -1;
namedWindow( "Example2_5-in", WINDOW_AUTOSIZE );
namedWindow( "Example2_5-out", WINDOW_AUTOSIZE );
// Create a window to show our input image
//
imshow( "Example2_5-in", image );
// Create an image to hold the smoothed output
//
Mat out;
// Do the smoothing
// ( Note: Could use GaussianBlur(), blur(), medianBlur() or bilateralFilter(). )
//
GaussianBlur( image, out, Size(5,5), 3, 3);
GaussianBlur( out, out, Size(5,5), 3, 3);
// Show the smoothed image in the output window
//
imshow( "Example2_5-out", out );
// Wait for the user to hit a key, windows will self destruct
//
waitKey( 0 );
}