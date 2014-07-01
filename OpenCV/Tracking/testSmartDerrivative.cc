#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>
#include "Derriv.cc"

#define EDGES_WINDOW "EDGES SON"
#define ORIGINAL_IMAGE "Original Image"
#define ESC_KEY 1048603 // Escape key on hp-elitebook

typedef cv::Vec3b px; // "px" for pixel 

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

// Returns the sum of all three channels of a given pixel
const int rgbSum( const px &rgb ){
  return (rgb[0]+rgb[1]+rgb[2]);
}

// Returns the max of two integers as an integer, defaults to a
const int& max( const int &a, const int &b ){
  if (a >= b)
    return a;
  return b;
}

// TODO:  This function will dynamically change the "step" amount of
//        the for loops based off of regional similartiy.
void smartDerrivative(const cv::Mat &inImg, cv::Mat &outImg,
		      const int &simCap, const int &divisor){
  int rowStep(1);
  int colStep(1);
  px previous(inImg.at<px>(0,0));
  px difference(0,0,0);
  for (int row(0); row<inImg.rows; row+=rowStep){
    for (int col(0); col<inImg.cols; col+=colStep){
      difference = previous - inImg.at<px>( row, col );
      outImg.at<px>( row, col ) = difference;
      previous = inImg.at<px>( row, col );
      colStep = (simCap - rgbSum(difference)) / divisor;
      if (colStep < 1)
	colStep = 1;
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

  int simCap(100);
  int divisor(10);
  int clear(0);

  cv::Mat imgDerriv(img.clone());
  imgDerriv.setTo(cv::Scalar(0,0,0));

  cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
  cv::namedWindow(EDGES_WINDOW, CV_WINDOW_NORMAL);

  cv::createTrackbar("simCap: ",EDGES_WINDOW,
  		     &simCap, 765 ,callbackDummy);
  cv::createTrackbar("divisor: ",EDGES_WINDOW,
  		     &divisor, 50 ,callbackDummy);
  cv::createTrackbar("clear (0=false): ", EDGES_WINDOW,
		     &clear, 1, callbackDummy);

  while (cv::waitKey(1) != ESC_KEY){
    if (argc < 2)
      vid >> img;
    if (divisor < 1)
      divisor = 1;
    if (clear)
      imgDerriv.setTo(cv::Scalar(0,0,0));
    smartDerrivative(img, imgDerriv, simCap, divisor);

    cv::imshow(ORIGINAL_IMAGE, img);
    cv::imshow(EDGES_WINDOW, imgDerriv);
  }
  return 0;
}
