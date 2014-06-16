#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define SETTINGS_PANEL "Adjust Panel"
#define WAIT_TIME 1

using namespace cv;
using namespace std;

  // data & Mat::at(int col, int row)
  // Size Mat::Size(void)

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

// Defined below main
void updateUserDisplay(Mat & testImg, int xCenter, int yCenter, 
		       int width, int height);

// This program is testing extracting sections of an image
int main(int argc, char *argv[]){
  if (argc != 2){
    std::cerr << "usage ./prog <img>" << std::endl;
    return -1;
  }

  int  xCenter	= 10;
  int  yCenter	= 10;
  int  width	= 4;
  int  height	= 4;
  Mat  testImg  = imread(argv[1], 1);
  Size imgSize  = testImg.size();
  namedWindow(SETTINGS_PANEL);
  createTrackbar("xCenter: ", SETTINGS_PANEL, &xCenter, 
		 imgSize.width - width, callbackDummy);
  createTrackbar("yCenter: ", SETTINGS_PANEL, &yCenter, 
		 imgSize.height - height, callbackDummy);
  createTrackbar("width:   ", SETTINGS_PANEL, &width, 
		 imgSize.width/2, callbackDummy);
  createTrackbar("height:  ", SETTINGS_PANEL, &height, 
		 imgSize.height/2, callbackDummy);
  for (; waitKey(WAIT_TIME) < 0 ;){
    updateUserDisplay(testImg, xCenter, yCenter, width, height);
  }

  return 0;
}

// Pre:  testImg defined, 
//       xCenter + width /2 < testImg.width
//       yCenter + height/2 < testImg.height
//       0 <= width  <= testImg.width /2
//       0 <= height <= testImg.height/2
// Post: The user is displayed a chopped image
void updateUserDisplay(Mat & testImg, int xCenter, int yCenter, 
		       int width, int height){
  if ((xCenter - width / 2) < 0)
    width = 2 * xCenter;
  if ((yCenter - height / 2) < 0)
    height = 2 * yCenter;

  Range rowRange(yCenter-height/2, yCenter+height/2);
  Range colRange(xCenter-width/2, xCenter+width/2);
  Mat regionScaled = testImg(rowRange, colRange);
  imshow("Original Image ", testImg);
  imshow("Region Image   ", regionScaled);    
}
