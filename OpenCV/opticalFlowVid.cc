#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector>

#define WAIT_TIME_MS 1   // Update delay time

using namespace cv;

int main( int argc, char *argv[] ){
  if (argc != 2){
    std::cerr << "usage ./prog <img>" << std::endl;
    return -1;
  }
  VideoCapture vid(argv[1]);
  Mat  imageOne, imageTwo;
  vid >> imageOne; vid >> imageTwo;
  Size imgSize  = imageOne.size();  // Assuming all images in vid are
                                    //  of the same size.

  // Move image one to image two and then get the next image from vid
  while ( !(waitKey(WAIT_TIME_MS)) ){
    imageTwo = imageOne;
    // WARNING:  This may cause problems if they end up sharing data
    vid >> imageOne;
    if (imageOne.total() > 0){
      opticalFlow(imageOne, imageTwo)
    }
    else{
      vid.open(argv[1]);
    }
  }

  return 0;
}

// TODO:  This function will do all the optical flow operations
void opticalFlow(Mat &imageOne, Mat &imageTwo){
  vector<KeyPoint> imgOnePoints ;
  vector<KeyPoint> imgTwoPoints ;  
  goodFeaturesToTrack(imageOne, imgOnePoints);
  goodFeaturesToTrack(imageOne, imgTwoPoints);
  calcOpticalFlowPyrLK(imageOne, imageTwo);
}
