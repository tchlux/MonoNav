#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used

using namespace cv;

int main(int argc, char *argv[]){
  // set up the parameters (check the defaults in opencv's code in
  // blobdetector.cpp)
  cv::SimpleBlobDetector::Params params;
  params.minDistBetweenBlobs = 10.0f;
  params.filterByInertia = false;
  params.filterByConvexity = false;
  params.filterByColor = false;
  params.filterByCircularity = false;
  params.filterByArea = true;
  params.minArea = 10.0f;
  params.maxArea = 10000.0f;
  // ... any other params you don't want default value

  // set up and create the detector using the parameters
  cv::SimpleBlobDetector blob_detector(params);
  vector<cv::KeyPoint> keypoints;

  // detect!
  Mat image;
  Mat blobs;
  VideoCapture vid(0);
  if (argc == 2)
    vid.open(argv[1]);
  for (;waitKey(1) < 0;){
    vid >> image;
    if (image.empty()){
      vid.open(argv[1]); vid >> image;
    }
    blob_detector.detect(image, keypoints);

    // extract the x y coordinates of the keypoints: 
    for (int i=0; i<keypoints.size(); i++){
      int X=keypoints[i].pt.x; 
      int Y=keypoints[i].pt.y;
      cv::circle(image, cv::Point(X,Y), 5, cv::Scalar(0,255,0));
    }
    namedWindow("Blob image", CV_WINDOW_NORMAL);
    imshow("Blob image", image);
    keypoints.clear();
  }

  return 0;
}
