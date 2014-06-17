#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used

// Pre:  same pre-requisites as updateUserDisplay
// Post: Extracts out a sparse data-set from the image provided
cv::Mat sparseRegion(cv::Mat &fullImg, int &xCenter, int &yCenter, 
		 int &width, int &height, int &pixelSpacing);
// ^^ Place at top of file if a header is necessary.

// Pre:  same pre-requisites as updateUserDisplay
// Post: Extracts out a sparse data-set from the image provided
cv::Mat sparseRegion(cv::Mat &fullImg, int &xCenter, int &yCenter, 
		 int &width, int &height, int &pixelSpacing){
  // Create a new cv::Mat of the appropriate size
  int rows(height / pixelSpacing);  int cols(width  / pixelSpacing);
  cv::Mat region(rows, cols, CV_8UC3);

  // Calculate lower bounds in original image
  int minX(xCenter - (width /2));  int minY(yCenter - (height/2));  

  // Copy over sparse data set
  for (int row(0); row < rows; row ++){
    for (int col(0); col < cols; col ++){
      region.at<cv::Vec3b>( row, col ) =
	fullImg.at<cv::Vec3b>(row*pixelSpacing+minY,
			      col*pixelSpacing+minX);
    }
  }
  return region;
}

// CV TYPES:
// CV_8UC1, CV_8UC2, CV_8UC3, for how many color channels there are
