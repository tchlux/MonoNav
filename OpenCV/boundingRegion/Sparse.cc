#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used

// Pre:  fullImg defined, pixelSpacing < (fullImg width or height)
// Post: Extracts out a sparse data-set from the image provided,
//       dropping 'pixelSpacing' pixels for every 1 pixel grabbed.
cv::Mat sparse(cv::Mat & fullImg, int &pixelSpacing);

// Pre:  fullImg defined
//       xCenter + width /2 < fullImg.width
//       yCenter + height/2 < fullImg.height
//       0 <= width  <= fullImg.width /2
//       0 <= height <= fullImg.height/2
//       0 <= pixelSpacing < min(width-1, height-1)
// Post: Extracts out a sparse data-set from the image provided
cv::Mat sparse(cv::Mat &fullImg, int &xCenter, int &yCenter, 
		 int &width, int &height, int &pixelSpacing);

// Pre:  fullImg defined, pixelSpacing < (fullImg width or height)
// Post: Extracts out a sparse data-set from the image provided,
//       dropping 'pixelSpacing' pixels for every 1 pixel grabbed.
cv::Mat sparse(cv::Mat & fullImg, int &pixelSpacing){
  int  xCenter(fullImg.cols / 2); // Default to center
  int  yCenter(fullImg.rows / 2);
  return sparse(fullImg, xCenter, yCenter, fullImg.cols, fullImg.rows, pixelSpacing);
}

// Pre:  fullImg defined
//       xCenter + width /2 < fullImg.width
//       yCenter + height/2 < fullImg.height
//       0 <= width  <= fullImg.width /2
//       0 <= height <= fullImg.height/2
//       0 <= pixelSpacing < min(width-1, height-1)
// Post: Extracts out a sparse data-set from the image provided
cv::Mat sparse(cv::Mat &fullImg, int &xCenter, int &yCenter, 
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
