#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector> // c++ vector class

#define LK_WINDOW "Lucas Kanade"
#define LK_DOT_COLOR 0,255,0

std::vector<cv::Point2f> g_lk_trackingPoints;
std::vector<cv::Point2f> g_lk_prevTrackingPoints;

cv::Size g_lk_winSize(10,10);
cv::TermCriteria g_lk_termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS
				    ,20,0.03);

int g_lk_minimumKeypoints(150);
int g_lk_maximumKeypoints(500);

// Pre:  drawImg is defined and has image data, trackingpoints have
//        already been found using LK algorithm, status is the listing
//        of statuses of all trackingpoints
// Post: Dots are draw on all the tracking points, previous tracking
//        points vector is resized according to current number of pts
void drawTrackingPoints(cv::Mat &drawImg,
			std::vector<uchar> &status){
  int numPoints(0);
  for(int tp(0); tp < g_lk_trackingPoints.size(); tp++ ){
    if( status[tp] ){ // If the status of the point is good
      g_lk_prevTrackingPoints[numPoints++] = g_lk_trackingPoints[tp];
      circle( drawImg, g_lk_prevTrackingPoints[tp], 3,
	      cv::Scalar(LK_DOT_COLOR), -1, 8);
    }
  }
  g_lk_prevTrackingPoints.resize(numPoints);
}

// Lucas Kanade algorithm on two images
// Pre:  grayImg and prevGrayImg are greyscale consecutive images from
//       a video.  grayImg.size() == prevGrayImg.size()
// Post: The lucas kanade algorithm is drawn on the image and then
//       displayed 
void LucasKanade(cv::Mat &grayImg, cv::Mat &prevGrayImg){  
  cv::Mat drawImg;
  cvtColor(prevGrayImg, drawImg, CV_GRAY2BGR); 

  if( g_lk_trackingPoints.size() < g_lk_minimumKeypoints ){
    goodFeaturesToTrack(grayImg, g_lk_trackingPoints, 
			g_lk_maximumKeypoints, 0.01, 10, 
			cv::Mat(), 3, 0, 0.04);
    cornerSubPix(grayImg, g_lk_trackingPoints, g_lk_winSize, 
		 cv::Size(-1,-1), g_lk_termcrit);
    g_lk_prevTrackingPoints = g_lk_trackingPoints;
  }
  std::vector<uchar> status;
  std::vector<float> err;
  calcOpticalFlowPyrLK(prevGrayImg, grayImg, g_lk_prevTrackingPoints,
		       g_lk_trackingPoints, status, err, g_lk_winSize,
		       3, g_lk_termcrit, 0);

  drawTrackingPoints(drawImg, status);

  imshow(LK_WINDOW, drawImg);

  // Swap the 'new' tracking info to the 'old' tracking info
  std::swap(g_lk_prevTrackingPoints, g_lk_trackingPoints);
  
}
