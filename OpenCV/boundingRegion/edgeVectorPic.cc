#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "Sparse.cc"
#include "Derriv.cc"
#include "Link.h"

#define ORIGINAL_IMAGE "Original"
#define EDGES_WINDOW "EDGES SON"

#define MOUSE_MOVE 0
#define MOUSE_LEFT_DN 1
#define MOUSE_LEFT_UP 4
#define MOUSE_RIGHT_DN 2
#define MOUSE_RIGHT_UP 5

#define CIRCLE_RADIUS 3

#define MAX_QUEUE_SIZE 100
#define BIG 9999999

using namespace cv;
using namespace std;

Mat g_sparseImg; // Holder for the original image (sparse)
Mat g_derriv;    // Holder for the derrivative of that image
Link<cv::Point> g_boundedRegion;
cv::Scalar g_green(0,255,0);
int g_interesting(15); // Greater than half intensity average
int g_checkRange(2);    // Neighborhood check range for breadth first

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

//Pre:  Point is defined and g_derriv is defined
//Post: true if the x,y point is on the image
bool inBounds(const cv::Point &pt){
  bool goodRow( (0 <= pt.y) && (pt.y < g_derriv.rows) );
  bool goodCol( (0 <= pt.x) && (pt.x < g_derriv.cols) );
  return( goodRow && goodCol );
}

//Pre:  point is inBounds of g_derriv and both are defined
//Post: true if the point meets or exceeds expectations
bool interesting(const cv::Point &pt){
  const px &pixel( g_derriv.at<px>(pt.y, pt.x) );
  return ((pixel.val[0] + pixel.val[1] + pixel.val[2]) 
	  <= g_interesting);
}

// TODO:  This will perform necessary checks on cells
void addIfInteresting(Link<cv::Point> &queue, const cv::Point &curr){
  if (inBounds(curr)){
    if (interesting(curr)){
      if (!queue.has(curr)){
	if (!g_boundedRegion.has(curr)){
	  queue.add(curr);
	}
      }
    }
  }
  else{
    std::cerr << "edgeVectorPic.cc Line 63: Out of bounds" << std::endl;
  }
}

//TODO:  This function will perform one step of "point addition" to
//       the queue that finds all bright enough pixels for a bounding
//       region
void stepQueue(Link<cv::Point> &queue){
  cv::Point check(queue[0]); // Create a copy of the first interest point
  for (int row=-g_checkRange; row<g_checkRange; row++){
    for (int col=-g_checkRange; col<g_checkRange; col++){
      // Loop around the interest point checking all in checkRange
      const cv::Point curr(check.x+col, check.y+row);      
      addIfInteresting(queue, curr);
    }
  }
  g_boundedRegion.add(check);
  queue.remove(0);
}

//TODO:  This function will use the current g_boundedRegion list to
//       draw a bounding box around an interesting area
void drawBoundingRegion(){
  cv::Point min(BIG,BIG);
  cv::Point max(0,0);
  int numPoints(g_boundedRegion.size());
  for (int i=0; i<numPoints; i++){
    int x(g_boundedRegion[0].x);
    int y(g_boundedRegion[0].y);
    g_derriv.at<px>(y,x) = px(0,255,0);
      //    rectangle(g_derriv, g_boundedRegion[0], g_boundedRegion[0], g_green);
    g_boundedRegion.spin();
  }
  imshow(EDGES_WINDOW, g_derriv);
}

// TODO:  This function will find all adjacent high intensity/edge
//        pixels in "g_derriv" and add them to "g_boundedRegion"
void completeRegion(){
  Link<cv::Point> queue;
  queue.add(g_boundedRegion[0]);
  while (queue.size() > 0){
    stepQueue(queue);
  }
}

// Pre:  event is the type event, x and y are the coordinates of the
//       mouse (top left origin), the last two args are useless
// Post: 
void mouseClick(int event, int x, int y, int, void*){
  // WARNING:  Not sure what "int, void*)" the last two args are for  
  if (event == MOUSE_LEFT_DN){
    g_boundedRegion.clear(); // Clear out any old data
    g_boundedRegion.add(Point(x,y));
    completeRegion();
    drawBoundingRegion();
  }
  else if (event == MOUSE_RIGHT_DN){
    g_derriv = derriv(g_sparseImg);
  }
}

// All edge pixels placed into vectors
int main(int argc, char *argv[]){
  if (argc != 2)
    return -1;
  int pixelSpacing(2);  // Default to 2 (25% image data)
  int prevPixelSpacing(pixelSpacing);
  Mat img(imread(argv[1])); // Open the image provided as command line arg

  g_sparseImg = sparse(img, pixelSpacing);
  g_derriv = derriv(g_sparseImg);

  //  namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
  namedWindow(EDGES_WINDOW, CV_WINDOW_NORMAL);
  createTrackbar("Threshold: ",EDGES_WINDOW,
		 &g_interesting, 255*3 ,callbackDummy);
  createTrackbar("Check Range: ",EDGES_WINDOW,
		 &g_checkRange, 5 ,callbackDummy);
  createTrackbar("Pixel Jump: ",EDGES_WINDOW,
		 &pixelSpacing, 10 ,callbackDummy);
  setMouseCallback(EDGES_WINDOW, mouseClick);
  for (;waitKey(1)<0;){
    if (pixelSpacing != prevPixelSpacing){
      g_sparseImg = sparse(img, pixelSpacing);
      g_derriv = derriv(g_sparseImg);      
      prevPixelSpacing = pixelSpacing;
    }
      
    imshow(EDGES_WINDOW, g_derriv);    
  }
  return 0;
}

