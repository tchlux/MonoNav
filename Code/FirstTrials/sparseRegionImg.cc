#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "sparseRegion.cc" // Function for region extraction

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
void updateUserDisplay(Mat &testImg, Size &imgSize, 
		       int xCenter, int yCenter,
		       int width, int height, int pixelSpacing);

// Defined below main
void verify(Size &imgSize, int &xCenter, int &yCenter,
	    int &width, int &height, int &pixelSpacing);

// Defined below main
bool userInputHandle(int &xCenter, int &yCenter, 
		     int &width, int &height, int &pixelSpacing);

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
  createTrackbar("xCenter: ",	    SETTINGS_PANEL, &xCenter,      imgSize.width,     callbackDummy);
  createTrackbar("yCenter: ",	    SETTINGS_PANEL, &yCenter,      imgSize.height,    callbackDummy);
  createTrackbar("width:   ",	    SETTINGS_PANEL, &width,        imgSize.width,     callbackDummy);
  createTrackbar("height:  ",	    SETTINGS_PANEL, &height,       imgSize.height,    callbackDummy);
  createTrackbar("pixelSpacing:  ", SETTINGS_PANEL, &pixelSpacing, MAX_PIXEL_SPACING, callbackDummy);

  // The waitKeys allow the windows to initialize before creating a
  //  new window, this ensures they do not stack on top of each other
  waitKey(ONE_SECOND_MS / 3);   
  namedWindow(IMAGE_WITH_REGION_RECTANGLE);
  imshow(IMAGE_WITH_REGION_RECTANGLE, testImg);

  waitKey(ONE_SECOND_MS / 3);
  namedWindow(REGION_IMAGE, WINDOW_NORMAL);

  // Main loop for viewing the image, uses the boolean returned by
  // "userInputHandle" to determine if the program should exit
  while (!(userInputHandle(xCenter, yCenter, width ,height ,
			   pixelSpacing))){
    updateUserDisplay(testImg, imgSize, 
		      xCenter, yCenter, 
		      width, height, pixelSpacing);
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
  bool exitProgram(false);
  int keyPress(waitKey(WAIT_TIME_MS));

  // TODO:  HACK I'm not sure why this value suddenly appeared
  if (keyPress != -1)
    keyPress -= 1048576;

  if (keyPress == NO_ACTION);
  else if (keyPress == A)
    xCenter -= MOVE_SPEED_PIXELS;
  else if (keyPress == D)
    xCenter += MOVE_SPEED_PIXELS;
  else if (keyPress == W)
    yCenter -= MOVE_SPEED_PIXELS;
  else if (keyPress == S)
    yCenter += MOVE_SPEED_PIXELS;
  else if (keyPress == J){
    width  += SCALE_RATE_PIXELS;
    height += SCALE_RATE_PIXELS;
  }
  else if (keyPress == K){
    width  -= SCALE_RATE_PIXELS;
    height -= SCALE_RATE_PIXELS;
  }
  else if (keyPress == I){
    if (pixelSpacing > 1)
      pixelSpacing --;
  }
  else if (keyPress == O){
    if (pixelSpacing < MAX_PIXEL_SPACING)
      pixelSpacing ++;
  }
  else // Any other key pressed
    exitProgram = true;
  return(exitProgram);
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
  Mat region(sparseRegion(testImg, xCenter, yCenter, 
			  width, height, pixelSpacing));
  //         ^^ Function defined in "sparseRegion.cc"

  // Deep copy the original image and add a rectangle demonstrating
  //  the current region bounds. Deep copy required to draw rectangle.
  Mat toDraw(testImg.clone());
  // WARNING:  This operation changes the runtime performace of this
  //           program.  Remove the lines immediately above and below
  //           this warning to more accurately test the performance of
  //           sparse region extraction.
  rectangle(toDraw, Point(minX,minY), Point(maxX,maxY), color);

  // Display the final pretty pictures
  imshow(IMAGE_WITH_REGION_RECTANGLE, toDraw);
  imshow(REGION_IMAGE, region);    
}

// Verifies the dimensions of the region the user requested, applies
//   restrictions if necessary according to image size (imgSize)
void verify(Size &imgSize, int &xCenter, int &yCenter,
	    int &width, int &height, int &pixelSpacing){
  // Cover zero cases (can't be avoided with OpenCV trackbars)
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
