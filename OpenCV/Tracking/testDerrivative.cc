#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>

#define EDGES_WINDOW "EDGES SON"
#define ORIGINAL_IMAGE "Original Image"

typedef cv::Vec3b px; // "px" for pixel 

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

// TODO:  This function will take an image's derrivative given a
//        Point that is the relative comparison point independent
//        comparison locations
void derrivative(const cv::Mat &inImg, cv::Mat &outImg, 
		 const cv::Point &from){
  int rowStep(from.y);
  int colStep(from.x);
  if (rowStep <= 0){
    if (rowStep < 0)
      rowStep *= -1;
    else
      rowStep = 1;
  }
  if (colStep <= 0){
    if (colStep < 0)
      colStep *= -1;
    else
      colStep = 1;
  }
  // Guarantee a positive step amount

  for (int row(rowStep); row < (inImg.rows-rowStep); row+=rowStep){
    for (int col(colStep); col < (inImg.cols-colStep); col+=colStep){
      outImg.at<px>( row, col ) = 
	inImg.at<px>( row, col ) -
	inImg.at<px>( row+from.y, col+from.x );
    }
  }  
}


// TODO:  This function will provide testing ground for the vector
//        based image derrivative
int main(int argc, char *argv[]){
  cv::VideoCapture vid(0);
  cv::Mat img; // Open the image provided
  vid >> img;
  if (argc >= 2)
    img = cv::imread(argv[1]);
  cv::Mat imgDerriv(img.clone());
  int xShift(6);  int yShift(5);
  cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
  cv::namedWindow(EDGES_WINDOW, CV_WINDOW_NORMAL);
  cv::createTrackbar("X Shift: ",EDGES_WINDOW,
		     &xShift, 10 ,callbackDummy);
  cv::createTrackbar("Y Shift: ",EDGES_WINDOW,
		     &yShift, 10 ,callbackDummy);
  while (cv::waitKey(1) != 1048603){
    if (img.empty()){
      vid.open(argv[1]);
      vid >> img;
    }
    derrivative(img, imgDerriv, cv::Point(xShift-5,yShift-5));
    cv::imshow(ORIGINAL_IMAGE, img);
    cv::imshow(EDGES_WINDOW, imgDerriv);
    vid >> img;
  }

  return 0;
}
