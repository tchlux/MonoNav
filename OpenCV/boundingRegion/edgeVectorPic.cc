#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "Sparse.cc"
#include "Derriv.cc"
#include <vector>

#define ORIGINAL_IMAGE "Original"
#define EDGES_WINDOW "EDGES SON"

#define MOUSE_MOVE 0
#define MOUSE_LEFT_DN 1
#define MOUSE_LEFT_UP 4
#define MOUSE_RIGHT_DN 2
#define MOUSE_RIGHT_UP 5

#define CIRCLE_RADIUS 3

using namespace cv;
using namespace std;

Mat g_sparseImg; // Holder for the original image (sparse)
Mat g_derriv;    // Holder for the derrivative of that image
vector<cv::Point> boundedRegion;
cv::Scalar g_green(0,255,0);

// TODO:  This function will find all adjacent high intensity/edge
//        pixels in "g_derriv" and add them to "boundedRegion"
void completeRegion(){
  
}

// Pre:  event is the type event, x and y are the coordinates of the
//       mouse (top left origin), the last two args are useless
// Post: 
void mouseClick(int event, int x, int y, int, void*){
  // WARNING:  Not sure what "int, void*)" the last two args are for  
  if (event == MOUSE_LEFT_DN){
    boundedRegion.clear(); // Clear out any old data
    boundedRegion.push_back(Point(x,y));

    completeRegion();

    circle(g_derriv, cv::Point(x,y), CIRCLE_RADIUS, g_green);
    imshow(EDGES_WINDOW, g_derriv);
  }
}

// All edge pixels placed into vectors
int main(int argc, char *argv[]){
  if (argc != 2)
    return -1;
  int pixelSpacing(2);  // Default to 2 (25% image data)
  Mat img(imread(argv[1])); // Open the image provided as command line arg

  g_sparseImg = sparse(img, pixelSpacing);
  g_derriv = derriv(g_sparseImg);

  //  namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
  namedWindow(EDGES_WINDOW, CV_WINDOW_NORMAL);

  setMouseCallback(EDGES_WINDOW, mouseClick);

  imshow(EDGES_WINDOW, g_derriv);
  waitKey(0);
  return 0;
}

