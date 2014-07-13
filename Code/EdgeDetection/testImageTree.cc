#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>
#include "ImageTree.cc"

using namespace cv;

int main(int argc, char *argv[]){
  if (argc != 2)
    return -1;
  int maxDepth(10);
  cv::Mat img(imread(argv[1]));
  it::_image = &img; 
  it::ImageTree(5);
  it::showImageTree();
  return 0;
}
