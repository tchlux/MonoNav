/**
 * @function cornerHarris_Demo.cpp
 * @brief Demo code for detecting corners using Harris-Stephens method

 * @author OpenCV team
 */

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define TRACKBAR_WINDOW "Trackbars for settings"
#define SOURCE_WINDOW "Source image"
#define CROPPED_WINDOW "Cropped image"
#define SOBEL_WINDOW_X "Sobel Derrivative X"
#define SOBEL_WINDOW_Y "Sobel Derrivative Y"
#define X_RANGE_START 300
#define X_RANGE_END 600
#define Y_RANGE_START 300
#define Y_RANGE_END 600

#define WAIT_MS 1 // Milisecond wait


// The sobel derrivative function
void sobelDerriv( Mat & origImg, int & xRangeCenter, 
		  int & yRangeCenter, int & rangeSize);

// Used as a dummy callback
void dummy(int, void*){}

// Pre:  argc == 2 where argv[1] == .avi video file
// Post: The corneres detected in this video are drawn
int main( int argc, char** argv )
{
  if (argc != 2)
    {
      std::cerr << "usage: ./sobelDerrivVid videoFile.avi" << 
	std::endl;
      return -1;
    }
  
  Mat origImg; // Original image holder
  VideoCapture vid(argv[1]); // Open video file
  vid >> origImg; // Get the first image

  // Initialize named windows for displaying video
  namedWindow( TRACKBAR_WINDOW, WINDOW_NORMAL );
  namedWindow( SOURCE_WINDOW, WINDOW_NORMAL );
  namedWindow( CROPPED_WINDOW, WINDOW_NORMAL );
  namedWindow( SOBEL_WINDOW_X, WINDOW_NORMAL );
  namedWindow( SOBEL_WINDOW_Y, WINDOW_NORMAL );
  Size origImgSize = origImg.size();
  int xRangeCenter = origImgSize.width  / 2;
  int yRangeCenter = origImgSize.height / 2;
  int rangeSize = (origImgSize.width + origImgSize.height) / 32;
  createTrackbar( "X Center: ", TRACKBAR_WINDOW, &xRangeCenter, 
		  origImgSize.width, dummy );
  createTrackbar( "Y Center: ", TRACKBAR_WINDOW, &yRangeCenter, 
		  origImgSize.height, dummy );
  createTrackbar( "Range Size: ", TRACKBAR_WINDOW, &rangeSize, 
		  rangeSize * 4, dummy );
  std::cerr << "origImgSize: " << origImgSize << std::endl;
  std::cerr << "xRangeCenter: " << xRangeCenter << std::endl;
  std::cerr << "yRangeCenter: " << yRangeCenter << std::endl;
  std::cerr << "rangeSize: " << rangeSize << std::endl;
  for (; ! (waitKey(WAIT_MS)>0) ;) // Loop until key press
    {
      vid >> origImg;
      if (origImg.total() > 0){
	imshow( SOURCE_WINDOW, origImg );
	sobelDerriv( origImg, xRangeCenter, yRangeCenter, rangeSize);
      }    
      else{
	vid.release(); // Release the video file (free memory)
        vid.open(argv[1]); // Reopen the file and loop
      }
    }
  return 0; // Normal execution complete
}


// Pre:  origImg, xRangeCenter, yRangeCenter, rangeSize all defined
// Post: The Sobel gradient for the image is displayed in an
//       alternate window that should have been initialized before
//       this function calls.  One window for x derrivative, one for
//       the y, and these are adjustable by trackbars in the source
//       image viewing window
void sobelDerriv( Mat & origImg, int &xRangeCenter, int &yRangeCenter,
		  int & rangeSize)
{
  int xLow, xHigh, yLow, yHigh;
  xLow = xRangeCenter - rangeSize; yLow = yRangeCenter - rangeSize;
  xHigh = xRangeCenter + rangeSize; yHigh = yRangeCenter + rangeSize;
  Range xRange(xLow, xHigh);
  Range yRange(yLow, yHigh);
  Mat extractedImage(origImg(yRange,xRange));
  Mat sobelDerrivX, sobelDerrivY;

  Sobel(extractedImage, sobelDerrivX, CV_8U, 1, 0);
  Sobel(extractedImage, sobelDerrivY, CV_8U, 0, 1);

  imshow( SOBEL_WINDOW_X, sobelDerrivX );
  imshow( SOBEL_WINDOW_Y, sobelDerrivY );
  imshow( CROPPED_WINDOW, extractedImage );
}
