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
  int pixelSpacing(9);  // Default to 2
  namedWindow(EDGES_WINDOW, CV_WINDOW_NORMAL); //On Vaio

  Mat sparseImg;
  Mat derrivImg;
  while ( waitKey(1) < 0 ){
    vid >> img;
    if (img.empty()){
      vid.open(argv[1]);
      vid >> img;
    }
    sparseImg = sparse(img, pixelSpacing);
    derrivImg = derriv(sparseImg);
    imshow(EDGES_WINDOW, derrivImg);
  }




  return 0;
}

