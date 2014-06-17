#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv/cxcore.h"

#define SETTINGS_PANEL "Adjust Panel"
#define IMAGE_WITH_RECT "Original Image"
#define REGION_IMAGE "Region Image"
#define REGION_SPARSE_IMAGE "Region Sparse Image"
#define WAIT_TIME 1   // Update delay time
#define NO_ACTION -1  // The OpenCV waitKey response when no keypress
#define MOVE_SPEED 4  // Rate that region position is changed by keys
#define SCALE_RATE 5  // Rate that region scale    is changed by keys

#define A 97   // left
#define D 100  // right
#define J 106  // shrink
#define K 107  // grow
#define S 115  // down
#define W 119  // up

#define BOX_COLOR 255,255,255,255 // Color of region rectangle outline

using namespace cv;
using namespace std;

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

// Defined below main
void verify(Size &imgSize, int &xCenter, int &yCenter,
	    int &width, int &height, int &pixelSpacing);

// Defined Below verify
bool userInputHandle(int &xCenter, int &yCenter, 
		     int &width, int &height);

// Defined below userInputHandle
Mat sparseRegion(Mat &fullImg, int &xCenter, int &yCenter, 
		 int &width, int &height, int &pixelSpacing);

// Defined below sparseRegion
void updateUserDisplay(Mat &testImg, Size &imgSize, 
		       int xCenter, int yCenter,
		       int width, int height, int pixelSpacing);

// This program tests/demonstrates extracting regions of an image
int main(int argc, char *argv[]){
  if (argc != 2){
    std::cerr << "usage ./prog <img>" << std::endl;
    return -1;
  }
  Mat  testImg  = imread(argv[1]);
  Size imgSize  = testImg.size();
  int  xCenter	= imgSize.width	  / 2; // Default to center
  int  yCenter	= imgSize.height  / 2;
  int  width	= xCenter; // Default to half actual image width
  int  height	= yCenter; // Default to half actual image height
  int  pixelSpacing = 1;   // Adjacent pixels

  namedWindow(SETTINGS_PANEL);
  createTrackbar("xCenter: ", SETTINGS_PANEL, &xCenter, 
  		 imgSize.width, callbackDummy);
  createTrackbar("yCenter: ", SETTINGS_PANEL, &yCenter, 
  		 imgSize.height, callbackDummy);
  createTrackbar("width:   ", SETTINGS_PANEL, &width, 
  		 imgSize.width, callbackDummy);
  createTrackbar("height:  ", SETTINGS_PANEL, &height, 
  		 imgSize.height, callbackDummy);
  createTrackbar("pixelSpacing:  ", SETTINGS_PANEL, &pixelSpacing, 
  		 20, callbackDummy);

  // The waitKeys allow the windows to initialize before creating a
  //  new window, this ensures they do not stack on top of each other
  waitKey(30);   namedWindow(IMAGE_WITH_RECT);
  imshow(IMAGE_WITH_RECT, testImg);
  waitKey(60);   namedWindow(REGION_IMAGE);
  // imshow(REGION_IMAGE, testImg);
  // waitKey(60);   namedWindow(REGION_SPARSE_IMAGE);

  // Main loop for viewing the image
  for (; !(userInputHandle(xCenter, yCenter, width, height)) ;){
    updateUserDisplay(testImg, imgSize, 
		      xCenter, yCenter, 
		      width, height, pixelSpacing);
  }
  return 0;
}

// Verifies the dimensions of the region the user requested, applies
//   restrictions if necessary according to image size (imgSize)
void verify(Size &imgSize, int &xCenter, int &yCenter,
	    int &width, int &height, int &pixelSpacing){
  // Cover zero cases (can't be avoided with OpenCV::highgui sliders)
  if (xCenter <= 0)
    xCenter = 1;
  if (yCenter <= 0)
    yCenter = 1;
  if (width <= 0)
    width = 2;
  if (height <= 0)
    height = 2;
  if (pixelSpacing <= 0)
    pixelSpacing = 1;
  // Cover exceeded lower bounds
  if ((xCenter - width  / 2) < 0)
    width  = 2 * xCenter;
  if ((yCenter - height / 2) < 0)
    height = 2 * yCenter;
  // Cover exceeded upper bounds
  if (xCenter >= imgSize.width)
    xCenter = imgSize.width - 1;
  if (yCenter >= imgSize.height)
    yCenter = imgSize.height - 1;
  if ((xCenter + width  / 2) >= imgSize.width)
    width  = 2 * (imgSize.width  - xCenter);
  if ((yCenter + height / 2) >= imgSize.height)
    height = 2 * (imgSize.height - yCenter);
}

// Provides key presses for region movement and scaling, any other
//   key causes the program to exit.  Keys are as follows:
// A  - move xCenter Left
// D  - move xCenter Right
// W  - move yCenter Up
// S  - move yCenter Down
// J  - increase width & height
// K  - decrease width & height
// Return: bool shouldExitProgram
bool userInputHandle(int &xCenter, int &yCenter, 
		     int &width, int &height){
  bool exitProgram(false);
  int keyPress(waitKey(WAIT_TIME));
  if (keyPress == NO_ACTION);
  else if (keyPress == A)
    xCenter -= MOVE_SPEED;
  else if (keyPress == D)
    xCenter += MOVE_SPEED;
  else if (keyPress == W)
    yCenter -= MOVE_SPEED;
  else if (keyPress == S)
    yCenter += MOVE_SPEED;
  else if (keyPress == J){
    width  += SCALE_RATE;
    height += SCALE_RATE;
  }
  else if (keyPress == K){
    width  -= SCALE_RATE;
    height -= SCALE_RATE;
  }
  else // Any other key pressed
    exitProgram = true;
  return(exitProgram);
}

// Pre:  same pre-requisites as updateUserDisplay
// Post: Extracts out a sparse data-set from the image provided
Mat sparseRegion(Mat &fullImg, int &xCenter, int &yCenter, 
		 int &width, int &height, int &pixelSpacing){
  Size imgSize(fullImg.size());
  // Non-sparse range bounds
  int minY(yCenter - (height/2));  int maxY(yCenter + (height/2));
  int minX(xCenter - (width /2));  int maxX(xCenter + (width /2));
  // Sparse range definitions
  Range rowRange(0, (maxY-minY) / pixelSpacing );
  Range colRange(0, (maxX-minX) / pixelSpacing );
  // Create a new Mat of the appropriate size
  Mat region = fullImg(rowRange, colRange).clone();
  // TODO:  This wastes time copying data that isn't used
  // Copy over sparse data set
  for (int row =  0; 
           row <  rowRange.end * pixelSpacing; 
           row += pixelSpacing){
    for (int col = 0;
             col < colRange.end * pixelSpacing;
             col += pixelSpacing){
      region.at<Vec3b>( row/pixelSpacing, col/pixelSpacing ) =
	fullImg.at<Vec3b>(row+minY,col+minX);
    }
  }
  return region;
}

// Pre:  testImg defined, imgSize defined
//       xCenter + width /2 < testImg.width
//       yCenter + height/2 < testImg.height
//       0 <= width  <= testImg.width /2
//       0 <= height <= testImg.height/2
//       0 <= pixelSpacing < min(width-1, height-1)
// Post: The user is displayed a selected region of the original image
void updateUserDisplay(Mat &testImg, Size &imgSize, 
		       int xCenter, int yCenter,
		       int width, int height, int pixelSpacing){
  verify(imgSize, xCenter, yCenter, width, height, pixelSpacing);
  // Range bounds
  int minY = yCenter-height/2;  int maxY = yCenter+height/2;
  int minX = xCenter-width /2;  int maxX = xCenter+width /2;
  // Range definitions
  Range rowRange(minY, maxY);
  Range colRange(minX, maxX);
  // Box Color
  Scalar color(BOX_COLOR);

  //  Get sub-section of image ("region") scaled
  Mat region = sparseRegion(testImg, xCenter, yCenter, 
			    width, height, pixelSpacing);

  // Deep copy the original image so that we can add a rectangle to it
  Mat toDraw = testImg.clone();
  rectangle(toDraw, Point(minX,minY), Point(maxX,maxY), color);

  // Display the final pretty pictures
  imshow(IMAGE_WITH_RECT, toDraw);
  imshow(REGION_IMAGE, region);    
}

