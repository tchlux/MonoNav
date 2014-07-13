#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>
#include "Link.h"             // Pixels to check
#include "List.h"

#define DEFAULT_JUMP 20 // 4% of original image
#define DEFAULT_MAX_DEPTH 3
#define DEFAULT_DEPTH_COLOR 255/DEFAULT_MAX_DEPTH
// Every "depth" increases pixel channels by 10
#define PIXEL_DIFF_THRESH 70*70

typedef List<cv::Point> pList; // "point" list or "pixel" list
//typedef Link<cv::Point> pList; // "point" list or "pixel" list
typedef cv::Vec3b px;


// Pre:  toCheck is defined as well as img.  jump > 0
// Post: The list "toCheck" is populated with a sparse pixel set
void populateList(pList &toCheck, const cv::Mat &img, const int &jump){
  for (int row(0); row<img.rows; row+=jump){
    for (int col(0); col<img.cols; col+=jump){
      toCheck.append(cv::Point(col,row));
    }
  }
}

// TODO:  Given a point and the derrivative image, it will determine
//        the depth that point was calculated at
int getDepthFromColor(const cv::Point &pt, const cv::Mat &dImage,
		      const int &dColor){
  return ( dImage.at<px>(pt.y, pt.x)[0] / dColor );
}

// Pre:  pixel is defined
// Post: The sum of the RGB channels of this pixel
int rgbSum(const px &pixel){
  return (pixel[0]+pixel[1]+pixel[2]);
}

// TODO:  This function checks if a pixel is interesting based on
//        whether it has already been checked and if it is different
//        enough from the currPixel (parent pixel)
void checkPixelInterest(const int &col, const int &row, pList &toCheck,
			const cv::Mat &image, cv::Mat &dImage,
			const int &interestColor, const int &currPixelSum){
  const px dPixelColor(dImage.at<px>(row, col));
  if (dPixelColor[0] < interestColor){
    const px checkPixel(image.at<px>(row, col));
    const int checkPixelSum(rgbSum(checkPixel));
    bool interesting( ((checkPixelSum-currPixelSum)*
		       (checkPixelSum-currPixelSum)) 
		      > PIXEL_DIFF_THRESH);
    if (interesting){
      // std::cerr << "toCheck.size(): " << toCheck.size() << std::endl;
      // std::cerr << "Col,row: " << "(" << col << "," << row << ")" << std::endl;
      toCheck.append(cv::Point(col,row));
      dImage.at<px>(row, col) = px(interestColor, interestColor, interestColor);
    }
  }
}

// TODO:  This function will check if a point is "interesting" using
//        differences in surrounding pixels, it will color interesting
//        pixels according to depth and add them to "toCheck"
void checkPointInterest(const cv::Point &curr, pList &toCheck,
			const cv::Mat &image, cv::Mat &dImage,
			const int &dColor, const int &depth){
  int rowRange( DEFAULT_JUMP );
  int colRange( DEFAULT_JUMP );
  rowRange >>= depth; // Divide by 2 "depth" times
  colRange >>= depth; // Divide by 2 "depth" times
  if (rowRange < 1)
    rowRange = 1;
  if (colRange < 1)
    colRange = 1;
  const int currPixelSum(rgbSum(image.at<px>(curr.y,curr.x)));
  const int interestColor(dColor*(depth+1));

  if (curr.y > rowRange)
    checkPixelInterest(curr.x, curr.y-rowRange, toCheck, image, 
		       dImage, interestColor, currPixelSum);
  if (curr.y+rowRange < image.rows)
    checkPixelInterest(curr.x, curr.y+rowRange, toCheck, image, 
		       dImage, interestColor, currPixelSum);
  if (curr.x > colRange)
    checkPixelInterest(curr.x-colRange, curr.y, toCheck, image, 
		       dImage, interestColor, currPixelSum);
  if (curr.x+colRange < image.cols)
    checkPixelInterest(curr.x+colRange, curr.y, toCheck, image, 
		       dImage, interestColor, currPixelSum);
}

// // TODO:  This function moves a "Stack" search forward one step,
// //        removing the current point and passing it to be checked
// void advanceStack(pList &toCheck, const cv::Mat &image, 
// 		  cv::Mat &dImage, const int &dColor,
// 		  const int &maxDepth){
//   cv::Point curr(toCheck[toCheck.size()-1]);
//   toCheck.remove(toCheck.size()-1);
//   int depth(getDepthFromColor(curr, dImage, dColor));
//   //  std::cerr << "depth: " << depth << std::endl;
//   if (depth <= maxDepth)
//     checkPointInterest(curr, toCheck, image, dImage, dColor, depth);
// }

// TODO:  This function moves a "Queue" search forward one step,
//        removing the current point and passing it to be checked
void advanceQueue(pList &toCheck, const cv::Mat &image, 
		  cv::Mat &dImage, const int &dColor,
		  const int &maxDepth){
  cv::Point curr(toCheck[0]);
  toCheck.remove(0);
  int depth(getDepthFromColor(curr, dImage, dColor));
  // std::cerr << "dImage.at<px>(curr.y,curr.x): " 
  // 	    << dImage.at<px>(curr.y,curr.x) 
  // 	    << std::endl;
  //  std::cerr << "toCheck: " << toCheck << std::endl;
  //  std::cerr << "depth: " << depth << std::endl;
  if (depth <= maxDepth)
    checkPointInterest(curr, toCheck, image, dImage, dColor, depth);
}

// TODO:  Image derrivative with tree approach
int main(int argc, char *argv[]){
  // Prepare image and derrivative storage
  cv::Mat image;
  cv::VideoCapture vid(0);
  if (argc != 2)
    vid >> image;
  else
    image = cv::imread(argv[1]);
  cv::Mat dImage(image.rows, image.cols, CV_8UC3);  
  dImage.setTo(cv::Scalar(0,0,0));

  // Prepare algorithm parameters
  int jump(DEFAULT_JUMP);
  int dColor(DEFAULT_DEPTH_COLOR);
  int maxDepth(DEFAULT_MAX_DEPTH);
  pList toCheck;
  // Prepare image and process
  cv::namedWindow("Original Image", CV_WINDOW_NORMAL);
  cv::namedWindow("Derrived Image", CV_WINDOW_NORMAL);
  while ( cv::waitKey(1)<0 ){
    populateList(toCheck, image, jump);  
    while (toCheck.size() > 0){
      advanceQueue(toCheck, image, dImage, dColor, maxDepth);
      //    advanceStack(toCheck, image, dImage, maxDepth, dColor);
    }
    cv::imshow("Original Image", image);
    cv::imshow("Derrived Image", dImage);
    vid >> image;
    dImage.setTo(cv::Scalar(0,0,0));
    toCheck.clear();
  }
  //  cv::waitKey(0);
  return 0;
}
