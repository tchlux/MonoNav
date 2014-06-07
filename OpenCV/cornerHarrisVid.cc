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

#define THRESH 220
#define MAX_THRESH 255
#define SOURCE_WINDOW "Source image"
#define CORNERS_WINDOW "Corners detected"

/// Detector parameters
#define BLOCKSIZE 2
#define APERTURESIZE 3
#define K 0.04

#define WAIT_MS 1

using namespace cv;
using namespace std;

/// Function header, defined after main
void cornerHarris_demo( Mat &srcImgGray);

// Callback, has no purpose here, for OpenCV trackbar
void callbackDummy( int, void* ){}

/**
 * @function main
 */
int main( int argc, char** argv ){
  if (argc != 2){
    std::cerr << "usage: ./cornerHarrisVid videoFile.avi" << 
      std::endl;
    return -1;
  }

  // Video stream holder and image holder
  VideoCapture srcVid( argv[1] );
  Mat srcImg, srcImgGray;
  int thresh = THRESH;
  // Initialize trackbar and windows for displaying images
  createTrackbar( "Threshold: ", SOURCE_WINDOW, &thresh, MAX_THRESH,
		  callbackDummy );
  namedWindow( SOURCE_WINDOW,  WINDOW_NORMAL );
  namedWindow( CORNERS_WINDOW, WINDOW_NORMAL );

  // Loop the video displaying both the source and cornerHarris
  for (; ! (waitKey(WAIT_MS)>0) ;){
    srcVid >> srcImg; // Extract first image
    if (srcImg.total() > 0){
      imshow( SOURCE_WINDOW, srcImg );

      /// Convert source image to gray and process cornerHarris
      cvtColor( srcImg, srcImgGray, COLOR_BGR2GRAY );
      cornerHarris_demo( srcImgGray );
    }
    else{
      srcVid.release(); // Release the video file (free memory)
      srcVid.open(argv[1]); // Reopen the file and loop
    }
  }

  return(0);
}

/**
 * @function cornerHarris_demo
 * @brief Executes the corner detection and draw a circle around the
 * possible corners
 */
void cornerHarris_demo( Mat &srcImgGray ){
  Mat dst, dst_norm, dst_norm_scaled;
  dst = Mat::zeros( srcImgGray.size(), CV_32FC1 );

  /// Detecting corners
  cornerHarris( srcImgGray, dst, BLOCKSIZE, APERTURESIZE, K,
		BORDER_DEFAULT );

  /// Normalizing
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  // /// Drawing a circle around corners
  // for( int j = 0; j < dst_norm.rows ; j++ )
  //   { for( int i = 0; i < dst_norm.cols; i++ )
  // 	{
  // 	  if( (int) dst_norm.at<float>(j,i) > THRESH )
  // 	    {
  // 	      circle( dst_norm_scaled, Point( i, j ), 5, Scalar(0), 2,
  // 		      8, 0 );
  // 	    }
  // 	}
  //   }
  /// Showing the result

  imshow( CORNERS_WINDOW, dst_norm_scaled );
}
