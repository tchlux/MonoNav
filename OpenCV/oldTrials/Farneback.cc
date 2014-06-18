#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used

#define FARNEBACK_WINDOW "Farneback"

// Draws lines in the image 'cflowmap' based off the values stored in 'flow'
void drawOptFlowMap(const cv::Mat &flow, cv::Mat &cflowmap, int step,
                    double scale, const cv::Scalar &color){
  for(int y = 0; y < cflowmap.rows; y += step){
    for(int x = 0; x < cflowmap.cols; x += step){
      const cv::Point2f &fxy = flow.at<cv::Point2f>(y, x);
      line(cflowmap, cv::Point(x,y), 
      	   cv::Point(cvRound(x+fxy.x), cvRound(y+fxy.y)), color);
    }
  }
}

// Farneback algorithm on two images
// Pre:  grayImg and prevGrayImg are greyscale consecutive images from a video
//       grayImg.size() == prevGrayImg.size()
// Post: The farneback algorithm is drawn on the image and then displayed
void Farneback(cv::Mat &grayImg, cv::Mat &prevGrayImg){
    cv::Mat flow, drawImg;
    calcOpticalFlowFarneback(prevGrayImg, grayImg, flow, 
			     0.5, 3, 15, 3, 5, 1.2, 0);
    cvtColor(grayImg, drawImg, CV_GRAY2BGR); // Color flow map
    drawOptFlowMap(flow, drawImg, 5, 1.5, CV_RGB(0, 255, 0)); // Add lines
    imshow(FARNEBACK_WINDOW, drawImg);
}
