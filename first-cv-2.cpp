
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    namedWindow( "Example 3", WINDOW_AUTOSIZE);
    VideoCapture cap;
    cap.open(string(argv[1]));

    Mat frame;
    for(;;) {
        cap >> frame;
        if (frame.empty()) break;
        imshow("Example 1", frame);
        if (waitKey(33) >= 0) break;
    }
    return 0;
}