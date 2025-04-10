/*------------------------------------------------------------------------------------------*\
This file contains material supporting chapter 12 of the book:
OpenCV3 Computer Vision Application Programming Cookbook
Third Edition
by Robert Laganiere, Packt Publishing, 2016.

This program is free software; permission is hereby granted to use, copy, modify,
and distribute this source code, or portions thereof, for any purpose, without fee,
subject to the restriction that the copyright notice may not be removed
or altered from any source or altered source distribution.
The software is released on an as-is basis and without any warranties of any kind.
In particular, the software is not guaranteed to be fault-tolerant or free from failure.
The author disclaims all warranties with regard to this software, any use,
and any consequent failure, is purely the responsibility of the user.

Copyright (C) 2016 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/

#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "videoprocessor.h"

void draw(const cv::Mat& img, cv::Mat& out) {

	img.copyTo(out);
	cv::circle(out, cv::Point(100,100),5,cv::Scalar(255,0,0),2);
}

// processing function
void canny(cv::Mat& img, cv::Mat& out) 
{
   // Convert to gray
   if (img.channels()==3)
      cv::cvtColor(img,out,cv::COLOR_BGR2GRAY);
   // Compute Canny edges
   cv::Canny(out,out,100,200);
   // Invert the image
   cv::threshold(out,out,128,255,cv::THRESH_BINARY_INV);
 }

		// int div = 32;
		// out = img.clone();
		// int nc= out.cols * out.channels();	
		// for (int j=0; j<out.rows; j++) {
		// 	// get the address of row j
		// 	uchar* data= out.ptr<uchar>(j);
		// 	for (int i=0; i<nc; i++) {
		// 	    // process each pixel 
		// 	    data[i]= (data[i]/div)*div + div/2;
		// 	}
		// }
void reduce(cv::Mat& img, cv::Mat& out)
{
		int div = 32;				//this is equivalent to the above
		out = img.clone();
		u_int8_t mask  = 0xE0;
		out=(out&cv::Scalar(mask,mask,mask)) + cv::Scalar(div/2,div/2,div/2);
}

void complement(cv::Mat& img, cv::Mat& out)
{
		// 	const int64 start = cv::getTickCount();
		    cv::subtract(cv::Scalar(255,255,255), img, out);	
		//    double duration = (cv::getTickCount() - start)/cv::getTickFrequency();
		// 	std::cout << "Time taken: " << duration << " seconds" << std::endl;
}



int main(int argc, char *argv[])
{


	// Create instance
	VideoProcessor processor;

	int opt;
	while ((opt = getopt(argc, argv, "abc")) != -1) 
	{
	  switch (opt) {
	  case 'a':
		// Set the frame processor callback function
		processor.setFrameProcessor(canny);
		break;
	  case 'b':
		processor.setFrameProcessor(reduce);
		break;
	  case 'c':
		processor.setFrameProcessor(complement);
		break;
	  default:break;
	  }
	}
/******************************************************/
	// Now using the VideoProcessor class

	// Open video file
	//processor.setInput("../Amarcord.mp4");
	processor.setInput(0);	//use camera

	// Declare a window to display the video
	processor.displayInput("Input Video");
	processor.displayOutput("Output Video");

	// Play the video at the original frame rate
	processor.setDelay(1000./processor.getFrameRate());

	// output a video
	processor.setOutput("bikeCanny.avi",-1,15);

	// stop the process at this frame
	processor.stopAtFrameNo(51);

	// Start the process
	processor.run();

	cv::waitKey();	

	return 0;
}
