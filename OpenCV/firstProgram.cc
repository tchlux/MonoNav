#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

// This program will display the image passed as a commandline arg
int main(int argc, char** argv ){
  int status = 0; // Run status of program

  if ( argc != 2 )    {
    printf("usage: DisplayImage.out <Image_Path>\n");
    status = -1;
  }
  Mat image; // http://docs.opencv.org/modules/core/doc/basic_structures.html#mat
  image = imread( argv[1], 1 );
  // http://docs.opencv.org/modules/highgui/doc/reading_and_writing_images_and_video.html#Mat%20imread%28const%20string&%20filename,%20int%20flags%29

  if ( !image.data ){
    printf("No image data \n");
    status = -1;
  }

  namedWindow("Display Image", CV_WINDOW_AUTOSIZE ); // Creates a
  //  window that the user can place an image in that can be referred
  //  to by the string parameter given
  imshow("Display Image", image);
  // The first paramater is the name of the window to put the image
  //  in, the second is the matrix for the image to be loaded into the
  //  window 
  waitKey(0);
  // Waits for a pressed key if = 0, otherwise, waits until the given
  //  number of miliseconds has ellapsed

  // http://docs.opencv.org/modules/highgui/doc/user_interface.html
  // ^^ Has all three of the above function calls

  return(status);
}
