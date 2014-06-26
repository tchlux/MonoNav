#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector> // c++ vector class

#define LK_WINDOW "Lucas Kanade"

std::vector<cv::Point2f> trackingPoints;     // Tracking points for LK algorithm
std::vector<cv::Point2f> prevTrackingPoints; // "^^" but from previous image

cv::Size winSize(10,10);
cv::TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
int minimumKeypoints(150);
int maximumKeypoints(500);

// Pre:  drawImg is defined and has image data, trackingpoints have
//        already been found using LK algorithm, status is the listing
//        of statuses of all trackingpoints
// Post: Dots are draw on all the tracking points
void drawTrackingPoints(cv::Mat &drawImg,
			std::vector<uchar> &status){
  int k(0);
  for(int i(0); i < trackingPoints.size(); i++ ){
    if( status[i] ){ // If the status of the point is good
      prevTrackingPoints[k++] = trackingPoints[i];
      circle( drawImg, prevTrackingPoints[i], 3, cv::Scalar(0,255,0), -1, 8);
    }
  }
  prevTrackingPoints.resize(k); // Resize so that uncopied points are dropped
}

// Lucas Kanade algorithm on two images
// Pre:  grayImg and prevGrayImg are greyscale consecutive images from a video
//       grayImg.size() == prevGrayImg.size()
// Post: The lucas kanade algorithm is drawn on the image and then displayed
void LucasKanade(cv::Mat &grayImg, cv::Mat &prevGrayImg){  
  cv::Mat drawImg;
  cvtColor(grayImg, drawImg, CV_GRAY2BGR); 

  if( trackingPoints.size() < minimumKeypoints ){
    goodFeaturesToTrack(grayImg, trackingPoints, 
			maximumKeypoints, 0.01, 10, 
			cv::Mat(), 3, 0, 0.04);
    cornerSubPix(grayImg, trackingPoints, winSize, cv::Size(-1,-1), termcrit);
    prevTrackingPoints = trackingPoints;
  }
  std::vector<uchar> status;
  std::vector<float> err;
  calcOpticalFlowPyrLK(prevGrayImg, grayImg, prevTrackingPoints, trackingPoints, 
		       status, err, winSize, 3, termcrit, 0);

  drawTrackingPoints(drawImg, status);

  imshow(LK_WINDOW, drawImg);

  // Swap the 'new' image info to the 'old' image info
  std::swap(prevTrackingPoints, trackingPoints);
  
}
