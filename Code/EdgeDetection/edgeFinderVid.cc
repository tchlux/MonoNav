#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "Sparse.cc"
#include "Derriv.cc"

#define EDGES_WINDOW "EDGES SON"

using namespace cv;


// All edge pixels placed into vectors
int main(int argc, char *argv[]){
  VideoCapture vid(0);
  if (argc == 2)
    vid.open(argv[1]);

  Mat img; // Open the image provided as command line arg
  int pixelSpacing(2);  // Default to 2
  Mat sparseImg;
  Mat derrivImg;
  namedWindow(EDGES_WINDOW, CV_WINDOW_NORMAL); //On Vaio

  vid >> sparseImg;
  vid >> derrivImg; // To ensure they are filled and the same size
  while ( waitKey(1) < 0 ){
    if (img.empty()){
      vid.open(argv[1]);
      vid >> img;
    }
    sparseImg = sparse(img, pixelSpacing);
    derriv(sparseImg, derrivImg);
    imshow(EDGES_WINDOW, derrivImg);
    vid >> img;
  }
  return 0;
}

