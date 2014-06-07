#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp" // For display windows
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream> // For sending output to terminal (cerr/cout)
#include <stdio.h>  //
#include <stdlib.h> //

#define SOURCE_VIDEO "Source video"
#define PROCESSED_VIDEO "Processed video"

using namespace cv;
using namespace std;

// Function Headers, defined below main
void lucasKanade( Mat &firstImg, Mat &secondImg );

// Performs the lucas-kanade algorithm on a video and displays the
// results in a window adjacent to the original image.
int main ( int argc, char *argv[] )
{
  if ( argc != 2 )
    {
      std::cerr << "usage: ./lucasKanadeVid videlFile.avi" 
		<< std::endl;
      return -1;
    }

  VideoCapture sourceVid ( argv[1] );
  Mat firstImg, secondImg; // Holder for adjacent source video images
  namedWindow( SOURCE_VIDEO,    WINDOW_NORMAL );
  namedWindow( PROCESSED_VIDEO, WINDOW_NORMAL );
  sourceVid >> secondImg;
  for (; ! waitKey(WAIT_MS) > 0 ;)
    {
      firstImg = secondImg;  // Cycle the frames
      sourceVid >> secondImgImg;
      if ( secondImg.size > 0 )
	{
	  imshow( SOURCEVID, secondImg );
	  lucasKanade(firstImg, secondImg);
	}
      else
	{
	  sourceVid.release();
	  sourceVid.open( argv[1] );
	}
    }

  return 0;
}

void printVector(vector<

// Pre:  
// Post: 
void lucasKanade( Mat &firstImg, Mat &secondImg )
{
  FeatureDetector *featureDetector = 
    FeatureDetector::create("GFTT"); // Use "Good features to track" 
                                     // algorithm to find features;
  vector<KeyPoint> firstKeyPoints;
  vector<KeyPoint> secondKeyPoints;

  featureDetector.detect(firstImg, firstKeyPoints);
  featureDetector.detect(firstImg, secondKeyPoints);


}
