#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp" // For display windows
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream> // For sending output to terminal (cerr/cout)
#include <stdio.h>  //
#include <stdlib.h> //

#define SOURCE_IMG "Source IMG"
#define PROCESSED_IMG "Processed IMG"

using namespace cv;
using namespace std;

// Demonstrates OpenCV feature detector in action.
int main( int argc, char *argv[] )
{
  if ( argc != 2 )
    {
      std::cerr << "usage: testFeatureDetectImg test1.img" 
		<< std::endl;
      return -1;
    }
  Mat sourceImage = imread( argv[1], 1 );
  Mat keyPointsImage;

  namedWindow( SOURCE_IMG,    WINDOW_NORMAL );
  namedWindow( PROCESSED_IMG, WINDOW_NORMAL );
  std::cerr << "testFeatureDetectImg.cc Line 28: " << std::endl;
  FeatureDetector *featureDetector =
    FeatureDetector::create("GFTT"); // Use "Good features to track" 
                                     // algorithm to find features;
  vector<KeyPoint> keyPoints;
  std::cerr << "testFeatureDetectImg.cc Line 33: " << std::endl;
  featureDetector->detect(sourceImage, keyPoints);
  std::cerr << "testFeatureDetectImg.cc Line 35: " << std::endl;
  drawKeypoints( sourceImage, keyPoints, keyPointsImage,
		 Scalar::all(-1),
		 DrawMatchesFlags::DRAW_RICH_KEYPOINTS ); 
  std::cerr << "testFeatureDetectImg.cc Line 39: " << std::endl;
  imshow( SOURCE_IMG,    sourceImage );
  imshow( PROCESSED_IMG, keyPointsImage );
  return 0;
}
