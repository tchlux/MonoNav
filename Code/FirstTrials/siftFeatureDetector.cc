#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#define IMAGE_DISPLAY_WINDOW "Image"
#define TRACKBAR_WINDOW "Testing SIFT"
#define MAX_WAIT_MS 300
#define MAX_NUM_FEATURES 5
#define MAX_OCTAVE_LAYERS 6
#define MAX_EDGE_THRESH 20
#define MAX_CONTRAST_THRESH 8

using namespace cv;

void readme();

int	g_wait_ms		= 1; 

int	g_numFeatures		= 0; 
int	g_octaveLayers		= 3; 
int	g_contrastThresh	= 4; 
int	g_edgeThresh		= 10;

// Callback, has no purpose here, for OpenCV trackbar
void callbackDummy( int, void* ){}

// Header, defined after main
void siftDetection( vector<Mat> & images, char *argv[] );

/** @function main */
int main( int argc, char *argv[] ){
  vector<Mat> images;
  for (int image=1; image < argc; image++){
    images.push_back( imread( argv[image] ) );
    namedWindow( argv[image], WINDOW_AUTOSIZE );
  }

  //-- Step 1: Detect the keypoints using SIFT Detector
  namedWindow( TRACKBAR_WINDOW );
  createTrackbar( "g_numFeatures: ", TRACKBAR_WINDOW, &g_numFeatures,
		  MAX_NUM_FEATURES, callbackDummy );
  createTrackbar( "g_octaveLayers: ", TRACKBAR_WINDOW, &g_octaveLayers,
		  MAX_OCTAVE_LAYERS, callbackDummy );
  createTrackbar( "g_contrastThresh: ", TRACKBAR_WINDOW, &g_contrastThresh,
		  MAX_CONTRAST_THRESH, callbackDummy );
  createTrackbar( "g_edgeThresh: ", TRACKBAR_WINDOW, &g_edgeThresh,
		  MAX_EDGE_THRESH, callbackDummy );

  siftDetection( images, argv );
  return 0;
}

// Pre:  image is defined
// Post: The keypoints in image are located using a
//       siftFeatureDetector and then displayed in a window
void siftDetection( vector<Mat> &images, char *argv[] ){
  for (; ! (waitKey(g_wait_ms) > 0) ;){
    if ( (g_octaveLayers > 0) ){
      //	  SIFT detector;
      SIFT detector( g_numFeatures, g_octaveLayers, 
		     ((float) g_contrastThresh) / 100, g_edgeThresh  );
      for (int img=0; img<images.size(); img++){
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
void readme(){
  std::cout << " Usage: ./SIFT_detector <img1>" << std::endl;
}
