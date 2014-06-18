#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#define IMAGE_DISPLAY_WINDOW "Image"
#define TRACKBAR_WINDOW "Testing SURF"
#define MAX_HESSIAN 10000 
#define MAX_WAIT_MS 300
#define MAX_OCTAVELAYERS 8
#define MAX_NUMOCTAVES 16
#define MAX_EXTENDED 1
#define MAX_UPRIGHT 1


using namespace cv;

void readme();

int g_wait_ms = 1; // The milisecond wait between updates
int g_minHessian = 2000; // The hessian value for the detector
int g_numOctaves = 1; // Number of gaussian pyramid octaves, bigger
		      // numbers detect bigger features
int g_octaveLayers = 1; // Number of images within each octave
int g_extended = 0; // True if extended descriptors should be computed
int g_upright = 1;  // True if orientation does not need to be computed

// Callback, has no purpose here, for OpenCV trackbar
void callbackDummy( int, void* ){}

// Header, defined after main
void surfDetection( vector<Mat> & images, char *argv[] );

/** @function main */
int main( int argc, char *argv[] )
{
  vector<Mat> images;
  for (int image=1; image < argc; image++)
    {
      images.push_back( imread( argv[image] ) );
      namedWindow( argv[image], WINDOW_AUTOSIZE );
    }

  //-- Step 1: Detect the keypoints using SURF Detector
  namedWindow( TRACKBAR_WINDOW );
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

  surfDetection( images, argv );
  return 0;
}

// Pre:  image is defined
// Post: The keypoints in image are located using a
//       surfFeatureDetector and then displayed in a window
void surfDetection( vector<Mat> &images, char *argv[] )
{
  for (; ! (waitKey(g_wait_ms) > 0) ;)
    {
      if ( (g_minHessian   > 0) &&
	   (g_numOctaves   > 0) &&
	   (g_octaveLayers > 0) )
	{
	  SURF detector( g_minHessian, g_numOctaves,
	  		 g_octaveLayers, g_extended,
	  		 g_upright  );
	  for (int img=0; img<images.size(); img++)
	    {
	      // surfDetector(images[img]);

	      std::vector<KeyPoint> keypoints;
	      detector.detect( images[img] , keypoints );
	      //-- Draw keypoints
	      Mat img_keypoints;
	      drawKeypoints( images[img], keypoints, img_keypoints,
	      		     Scalar::all(-1), 
	      		     DrawMatchesFlags::DEFAULT );

	      //-- Show detected (drawn) keypoints
	      imshow( argv[img+1] , img_keypoints );
	    }
	}
    }
}

/** @function readme */
void readme()
{ std::cout << " Usage: ./SURF_detector <img1>" << std::endl; }
