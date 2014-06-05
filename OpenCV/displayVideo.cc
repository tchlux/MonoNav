#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

// This program will display the image passed as a commandline arg
int main(int argc, char** argv ){
  int status = 0; // Run status of program

  if (argc != 2){
    printf("usage: displayVideo <Video_Path>\n");
    status = -1;
  }
  else{
    VideoCapture vid(argv[1]);
    namedWindow("Testing Video");

    while (true){
      Mat frame;
      vid >> frame;
      if (frame.total() > 0)
	imshow("Testing Video", frame);
      if (waitKey(20) >= 0) break;
    }
  }
  return(status);
}
