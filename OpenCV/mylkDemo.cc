#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

#define LK_DEMO_WINDOW "LK Demo"
#define WAIT_TIME_MS 1
#define LOWER_THRESHOLD_KEYPOINT 150
// If there are less than this many points it will recalculate

using namespace cv;
using namespace std;

Point2f pt;
bool addRemovePt = false;

int main( int argc, char** argv ){
  if (argc != 2){
    std::cerr << "usage: ./lkdem <video.avi>" << std::endl;
    return -1;
  }

  VideoCapture cap;
  TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
  Size winSize(10,10);
    
  const int MAX_COUNT = 500;
  bool needToInit = false;
  bool nightMode = false;

  cap.open(argv[1]);  
  if( !cap.isOpened() ){
    cout << "Could not initialize capturing...\n";
    return 0;
  }    


  namedWindow( LK_DEMO_WINDOW );

  Mat gray, prevGray, image;
  vector<Point2f> points[2];
    
  while (waitKey(WAIT_TIME_MS) < 0){
    Mat frame;
    cap >> frame;

    if (frame.empty()){
      cap.open(argv[1]);
      cap >> frame;
    }

    frame.copyTo(image);
    cvtColor(image, gray, CV_BGR2GRAY); 

    if( needToInit ){
      // automatic initialization
      goodFeaturesToTrack(gray, points[1], MAX_COUNT, 
			  0.01, 10, Mat(), 3, 0, 0.04);
      cornerSubPix(gray, points[1], winSize, Size(-1,-1), termcrit);
      addRemovePt = false;
    }
    else if( !points[0].empty() ){
      vector<uchar> status;
      vector<float> err;
      if(prevGray.empty())
	gray.copyTo(prevGray);
      calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], 
			   status, err, winSize, 3, termcrit, 0);
      size_t i, k;
      for( i = k = 0; i < points[1].size(); i++ ){
	if( addRemovePt ){
	  if( norm(pt - points[1][i]) <= 5 ){
	    addRemovePt = false;
	    continue;
	  }
	}

	if( !status[i] )
	  continue;

	points[1][k++] = points[1][i];
	circle( image, points[1][i], 3, Scalar(0,255,0), -1, 8);
      }
      points[1].resize(k);
    } // End if !points[0].empty()

    needToInit = false;
    imshow(LK_DEMO_WINDOW, image);

    if( waitKey(10) < 0 )
      if (points[0].size() < (size_t)LOWER_THRESHOLD_KEYPOINT)
	needToInit = true;
      else;
    else break;
    std::swap(points[1], points[0]);
    swap(prevGray, gray);
  }
  return 0;
}
