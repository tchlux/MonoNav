#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#define IMAGE_DISPLAY_WINDOW "Image"
#define TRACKBAR_WINDOW "Testing SURF"
#define MAX_HESSIAN 700
#define MAX_WAIT_MS 300
#define MAX_OCTAVELAYERS 16
#define MAX_NUMOCTAVES 32
#define MAX_EXTENDED 1
#define MAX_UPRIGHT 1


using namespace cv;

void readme();

int g_wait_ms = 1; // The milisecond wait between updates
int g_minHessian = 300; // The hessian value for the detector
int g_numOctaves = 1; // Number of gaussian pyramid octaves, bigger
		      // numbers detect bigger features
int g_octaveLayers = 2; // Number of images within each octave
int g_extended = 0; // True if extended descriptors should be computed
int g_upright = 1;  // True if orientation does not need to be computed

// Callback, has no purpose here, for OpenCV trackbar
void callbackDummy( int, void* ){}

// Header, defined after main
void surfDetection( Mat & sourceImage );

/** @function main */
int main( int argc, char *argv[] )
{
  if ( argc != 2 ) 
    { 
      std::cerr << "usage: ./surfFeatureDetectorVideo video.avi" 
		<< std::endl;
      return -1;
    }

  VideoCapture sourceVideo( argv[1] );
  Mat sourceImage;

  //-- Step 1: Detect the keypoints using SURF Detector
  namedWindow( TRACKBAR_WINDOW );
  namedWindow( IMAGE_DISPLAY_WINDOW , WINDOW_NORMAL );

  createTrackbar( "Update wait ms: ", TRACKBAR_WINDOW, &g_wait_ms,
		  MAX_WAIT_MS, callbackDummy );
  createTrackbar( "Min Hessian: ", TRACKBAR_WINDOW, &g_minHessian,
		  MAX_HESSIAN, callbackDummy );
  createTrackbar( "g_numOctaves: ", TRACKBAR_WINDOW, &g_numOctaves,
		  MAX_NUMOCTAVES, callbackDummy );
  createTrackbar( "g_octaveLayers: ", TRACKBAR_WINDOW, &g_octaveLayers,
		  MAX_OCTAVELAYERS, callbackDummy );
  createTrackbar( "g_extended: ", TRACKBAR_WINDOW, &g_extended,
		  MAX_EXTENDED, callbackDummy );
  createTrackbar( "g_upright: ", TRACKBAR_WINDOW, &g_upright,
		  MAX_UPRIGHT, callbackDummy );

  for (; ! (waitKey(g_wait_ms) > 0) ;)
    {
      sourceVideo >> sourceImage;
      if ( sourceImage.total() > 0)
	{
	  surfDetection( sourceImage );      	  
	}
      else
	{
	  sourceVideo.release();
	  sourceVideo.open( argv[1] );
	}
    }
  return 0;
}

// Pre:  image is defined
// Post: The keypoints in image are located using a
//       surfFeatureDetector and then displayed in a window
void surfDetection( Mat & sourceImage )
{
  if ( (g_minHessian   > 0) &&
       (g_numOctaves   > 0) &&
       (g_octaveLayers > 0) )
    {
      SurfFeatureDetector detector( g_minHessian, g_numOctaves,
				    g_octaveLayers, g_extended,
				    g_upright  );
      std::vector<KeyPoint> keypoints;
      detector.detect( sourceImage , keypoints );
      //-- Draw keypoints
      Mat img_keypoints;
      drawKeypoints( sourceImage, keypoints, img_keypoints,
		     Scalar::all(-1), 
		     DrawMatchesFlags::DEFAULT );

      //-- Show detected (drawn) keypoints
      imshow( IMAGE_DISPLAY_WINDOW , img_keypoints );
    }
}

/** @function readme */
void readme()
{ std::cout << " Usage: ./SURF_detector <img1>" << std::endl; }
