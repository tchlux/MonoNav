#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "sparseRegion.cc" // Function for region extraction
#include "Farneback.cc"    // Function for computing and drawing
                           //  farneback algorithm on two images

#define SETTINGS_PANEL "Adjust Panel"
#define IMAGE_WITH_REGION_RECTANGLE "Original Image"
#define WAIT_TIME_MS 1   // Update delay time
#define NO_ACTION -1  // The OpenCV waitKey response when no keypress
#define MOVE_SPEED_PIXELS 4  // Rate that region position is changed by keys
#define SCALE_RATE_PIXELS 5  // Rate that region scale    is changed by keys
#define ONE_SECOND_MS 1000 // Milliseconds in one second
#define MAX_PIXEL_SPACING 20 // max ratio for dropping pixels (20:1)

// Key Press identifiers --> The comment gives the function of the key
#define A 97   // region left
#define D 100  // region right
#define I 105  // increase region resolution
#define J 106  // shrink region bounds
#define K 107  // grow region bounds
#define O 111  // decrease region resolution
#define S 115  // region down
#define W 119  // region up

#define BOX_COLOR 255,255,255,255 // Color of region rectangle outline

using namespace cv;

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

// Defined below main
void verify(Size &imgSize, int &xCenter, int &yCenter,
	    int &width, int &height, int &pixelSpacing);

// Defined below main
bool userInputHandle(int &xCenter, int &yCenter, 
		     int &width, int &height, int &pixelSpacing);

// This program tests/demonstrates extracting regions of an image
int main(int argc, char *argv[]){
  VideoCapture vid(0);
  if (argc == 2)
    vid.open(argv[1]);

  int  pixelSpacing = 3;   // Adjacent pixels
  Mat  origImg;
  vid >> origImg;

  namedWindow(SETTINGS_PANEL);
  createTrackbar("pixelSpacing:  ", SETTINGS_PANEL, &pixelSpacing,
		 MAX_PIXEL_SPACING, callbackDummy);

  waitKey(ONE_SECOND_MS / 3);
  namedWindow(FARNEBACK_WINDOW, WINDOW_NORMAL);

  Mat prevgray, gray;
  vector<Point2f> points[2];

  // Main loop for viewing the image, uses the boolean returned by
  // "userInputHandle" to determine if the program should exit
  while (waitKey(WAIT_TIME_MS) < 0){
    if (pixelSpacing < 1) pixelSpacing = 1;

    vid >> origImg;
    if (!(origImg.total() > 0)){
      vid.open(argv[1]);
      vid >> origImg;
    }
    Mat choppedRegion = sparseRegion(origImg, pixelSpacing);
    cvtColor(choppedRegion, gray, CV_BGR2GRAY);
    if (gray.size() != prevgray.size()) gray.copyTo(prevgray);

    Farneback(gray, prevgray);

    std::swap(prevgray, gray); // Swap before continuing
  }
  return 0;
}

