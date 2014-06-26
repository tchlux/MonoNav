#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "Sparse.cc"
#include "Derriv.cc"
#include "Link.h"

#define ORIGINAL_IMAGE "Original"
#define EDGES_WINDOW "EDGES SON"

#define CIRCLE_RADIUS 3

#define ITER_SPACING 10
#define RESET_COUNT 2000

#define MAX_QUEUE_SIZE 100
#define BIG 9999999

using namespace cv;
using namespace std;

Mat g_sparseImg; // Holder for the original image (sparse)
Mat g_derriv;    // Holder for the derrivative of that image
Link<cv::Point> g_boundedRegion;
cv::Scalar g_green(0,255,0);
int g_interesting(280); // Greater than half intensity average
int g_checkRange(2);    // Neighborhood check range for breadth first

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

//Pre:  Point is defined and g_derriv is defined
//Post: true if the x,y point is on the image
bool inBounds(const cv::Point &pt){
  bool goodRow( 0 <= pt.y < g_derriv.rows );
  bool goodCol( 0 <= pt.x < g_derriv.cols );
  return( goodRow && goodCol );
}

//Pre:  point is inBounds of g_derriv and both are defined
//Post: true if the point meets or exceeds expectations
bool interesting(const cv::Point &pt){
  const px &pixel( g_derriv.at<px>(pt.y, pt.x) );
  return ((pixel.val[0] + pixel.val[1] + pixel.val[2]) 
	  >= g_interesting);
}

//TODO:  This function will perform one step of "point addition" to
//       the queue that finds all bright enough pixels for a bounding
//       region
void stepQueue(Link<cv::Point> &queue){
  cv::Point check(queue[0]); // Create a copy of the first interest point
  for (int row=-g_checkRange; row<g_checkRange; row++){
    for (int col=-g_checkRange; col<g_checkRange; col++){
      // Loop around the interest point checking all in checkRange
      cv::Point curr(check.x+col, check.y+row);
      if (inBounds(curr) && interesting(curr)){
	if (!queue.has(curr)){
	  if (!g_boundedRegion.has(curr)){
	    queue.add(curr);
	  }
	}
      }
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
    rectangle(g_derriv, g_boundedRegion[0], g_boundedRegion[0], g_green);
    g_boundedRegion.spin();
  }
}

// TODO:  This function will find all adjacent high intensity/edge
//        pixels in "g_derriv" and add them to "g_boundedRegion"
void completeRegion(){
  Link<cv::Point> queue;
  if (g_boundedRegion.size() > 0){
    queue.add(g_boundedRegion[0]);
    while (queue.size() > 0){
      stepQueue(queue);
    }
    drawBoundingRegion();
  }
}

// TODO:  This function translates an iteration to a point
cv::Point iterationToPoint(int iter){
  int x((iter*ITER_SPACING) % g_derriv.cols);

  int y(((iter*ITER_SPACING) / g_derriv.cols) * ITER_SPACING  );
  return cv::Point(x,y);
}

// TODO:  This function automates the process of finding interesting regions
void findInterestPoints(int iteration){
  if (iteration < RESET_COUNT){
    cv::Point possiblePoint(iterationToPoint(iteration));
    g_boundedRegion.clear(); // Clear out any old data
    g_boundedRegion.add(possiblePoint);
    std::cerr << "g_boundedRegion[0]: " << g_boundedRegion[0] << std::endl;
    completeRegion();
    imshow(EDGES_WINDOW, g_derriv);
  }
  else{
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
  int iteration(0); // Iterator variable
  for (;waitKey(1)<0;){
    iteration++;
    findInterestPoints(iteration);

    if (pixelSpacing != prevPixelSpacing){
      g_sparseImg = sparse(img, pixelSpacing);
      g_derriv = derriv(g_sparseImg);      
      prevPixelSpacing = pixelSpacing;
    }
    imshow(EDGES_WINDOW, g_derriv);    

    if (iteration >= RESET_COUNT)
      iteration = 0;
  }
  return 0;
}

