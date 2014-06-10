#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[]){
  if (argc != 2){
    std::cerr << "usage ./prog <img>" << std::endl;
    return -1;
  }
  Mat testImg, testImgGrey;
  testImg = imread(argv[1], 1);
  cvtColor(testImg, testImgGrey, COLOR_BGR2GRAY);
  Size imgSize = testImg.size();
  // data & Mat::at(int col, int row)
  // Size Mat::Size(void)

  return 0;
}
