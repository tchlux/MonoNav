#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used

using namespace cv;

int main(int argc, char *argv[]){
  if (argc != 2)
    return -1;
  Mat image(imread(argv[1]));
  // set up the parameters (check the defaults in opencv's code in
  // blobdetector.cpp)
  cv::SimpleBlobDetector::Params params;
  params.minDistBetweenBlobs = 50.0f;
  params.filterByInertia = false;
  params.filterByConvexity = false;
  params.filterByColor = false;
  params.filterByCircularity = false;
  params.filterByArea = true;
  params.minArea = 20.0f;
  params.maxArea = 500.0f;
  // ... any other params you don't want default value

  // set up and create the detector using the parameters
  cv::SimpleBlobDetector blob_detector(params);// = cv::SimpleBlobDetector(params);
  blob_detector.create("SimpleBlob");

  // detect!
  vector<cv::KeyPoint> keypoints;
  blob_detector.detect(image, keypoints);

  // extract the x y coordinates of the keypoints: 
  for (int i=0; i<keypoints.size(); i++){
    int X=keypoints[i].pt.x; 
    int Y=keypoints[i].pt.y;
    image.at<cv::Vec3b>(Y,X) = cv::Vec3b(0,255,0);
  }
  imshow("Blob image", image);
  waitKey(0);
  return 0;
}
