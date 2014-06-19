#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "sparseRegion.cc" // Function for region extraction
#include "Farneback.cc"
#include "LucasKanade.cc"
#include "Sobel.cc"
#include "SIFT.cc"
#include "SURF.cc"

#define SETTINGS_PANEL "Adjust Panel"
#define IMAGE_WITH_REGION_RECTANGLE "Original Image"
#define REGION_IMAGE "Region Image"
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

void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
                    double scale, const Scalar& color);

// This program tests/demonstrates extracting regions of an image
int main(int argc, char *argv[]){
  VideoCapture vid(0);
  if (argc == 2)
    vid.open(argv[1]);

  Mat  origImg;
  vid >> origImg;
  Size imgSize  = origImg.size();
  int  xCenter	= imgSize.width	  / 2; // Default to center
  int  yCenter	= imgSize.height  / 2;
  int  width 	= imgSize.width;  // Default to full width
  int  height	= imgSize.height; // Default to full height
  int  pixelSpacing  = 3;              // Adjacent pixels

  //  namedWindow(SETTINGS_PANEL, WINDOW_NORMAL); //On HP
  namedWindow(SETTINGS_PANEL, CV_WINDOW_NORMAL); //On Vaio
  createTrackbar("xCenter: ",	    SETTINGS_PANEL, &xCenter,      imgSize.width,     callbackDummy);
  createTrackbar("yCenter: ",	    SETTINGS_PANEL, &yCenter,      imgSize.height,    callbackDummy);
  createTrackbar("width:   ",	    SETTINGS_PANEL, &width,        imgSize.width,     callbackDummy);
  createTrackbar("height:  ",	    SETTINGS_PANEL, &height,       imgSize.height,    callbackDummy);
  createTrackbar("pixelSpacing:  ", SETTINGS_PANEL, &pixelSpacing, MAX_PIXEL_SPACING, callbackDummy);

  waitKey(ONE_SECOND_MS / 3);
  namedWindow(FARNEBACK_WINDOW, CV_WINDOW_NORMAL);
  namedWindow(LK_WINDOW,        CV_WINDOW_NORMAL);
  namedWindow(SIFT_WINDOW,      WINDOW_NORMAL);
  namedWindow(SURF_WINDOW,      WINDOW_NORMAL);
  //  namedWindow(SOBEL_WINDOW,     WINDOW_NORMAL);
  Mat prevgray, gray, flow, cflow;
  vector<Point2f> points[2];

  // Main loop for viewing the image, uses the boolean returned by
  // "userInputHandle" to determine if the program should exit
  while (!(userInputHandle(xCenter, yCenter, width ,height ,
			   pixelSpacing))){
    vid >> origImg;
    if (origImg.empty()){
      vid.open(argv[1]);
      vid >> origImg;
    }
    verify(imgSize, xCenter, yCenter, width, height, pixelSpacing);
    Mat choppedRegion(sparseRegion(origImg, xCenter, yCenter, 
				   width, height, pixelSpacing));
    cvtColor(choppedRegion, gray, CV_BGR2GRAY);
    if (gray.size() != prevgray.size())
      gray.copyTo(prevgray);

    Farneback(gray, prevgray);
    LucasKanade(gray, prevgray);
    siftDetector(choppedRegion);
    surfDetector(choppedRegion);    
    //    sobelDerriv(gray, 1);
    std::swap(prevgray, gray);
  }
  return 0;
}

// Provides key presses for region movement and scaling, any other
//   key causes the program to exit.  Keys are as follows:
// A  - move xCenter Left
// D  - move xCenter Right
// W  - move yCenter Up
// S  - move yCenter Down
// J  - increase width & height
// K  - decrease width & height
// I  - increase resolution of region (up to normal resolution)
// O  - decresae resolution of region
// Return: bool shouldExitProgram
bool userInputHandle(int &xCenter, int &yCenter, 
		     int &width, int &height, int &pixelSpacing){
  int keyPress(waitKey(WAIT_TIME_MS));
  bool exitProgram((keyPress == 1048603) || (keyPress == 27));
  return(exitProgram);
}

// Verifies the dimensions of the region the user requested, applies
//   restrictions if necessary according to image size (imgSize)
void verify(Size &imgSize, int &xCenter, int &yCenter,
	    int &width, int &height, int &pixelSpacing){
  // Cover zero cases (can't be avoided with OpenCV trackbars)
  if (xCenter < 1)
    xCenter = 1;
  if (yCenter < 1)
    yCenter = 1;
  if (width < 2)
    width = 2;
  if (height < 2)
    height = 2;
  if (pixelSpacing < 1)
    pixelSpacing = 1;
  // Cover excessive spacing cases
  if (width < pixelSpacing)
    width = pixelSpacing;
  if (height < pixelSpacing)
    height = pixelSpacing;
  // Cover exceeded lower bounds
  if ((xCenter - width  / 2) < 0)
    xCenter = width  / 2;
  if ((yCenter - height / 2) < 0)
    yCenter = height / 2;
  // Cover exceeded upper bounds
  if ((xCenter + width  / 2) >= imgSize.width)
    xCenter = imgSize.width  - (width  / 2) - 1;
  if ((yCenter + height / 2) >= imgSize.height)
    yCenter = imgSize.height - (height / 2) - 1;
}
