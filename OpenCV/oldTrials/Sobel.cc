#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#define SOBEL_WINDOW "Sobel Derrivative"

// Pre:  origImg, xRangeCenter, yRangeCenter, rangeSize all defined
// Post: The Sobel gradient for the image is displayed in an
//       alternate window that should have been initialized before
//       this function calls.  One window for x derrivative, one for
//       the y, and these are adjustable by trackbars in the source
//       image viewing window
void sobelDerriv( cv::Mat & origImg, int XorY){
  cv::Mat drawImg;
  int x = XorY == 0 ? 1 : 0;
  int y = XorY == 0 ? 0 : 1;
  Sobel(origImg, drawImg, CV_8U, x, y);
  imshow(SOBEL_WINDOW, drawImg);
}
