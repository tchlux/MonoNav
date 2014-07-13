#include "cv.h"
#include "highgui.h"
#include "sparseRegion.cc"

#define SETTINGS_PANEL "Adjust Panel"
#define MAX_PIXEL_SPACING 20 // max ratio for dropping pixels (20:1)

using namespace cv;

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
                    double scale, const Scalar& color)
{
  for(int y = 0; y < cflowmap.rows; y += step)
    for(int x = 0; x < cflowmap.cols; x += step)
      {
	const Point2f& fxy = flow.at<Point2f>(y, x);
	line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
	     color);
	circle(cflowmap, Point(x,y), 2, color, -1);
      }
}

int main(int argc, char** argv){
  VideoCapture cap(0);
  if (argc == 2)
    cap.open(argv[1]);
    
  Mat prevgray, gray, flow, cflow, frame;
  namedWindow("flow", 1);
  cap >> frame;  
    
  while (waitKey(10) < 0){
    cap >> frame;
    cvtColor(frame, gray, CV_BGR2GRAY);
    if( prevgray.data ){
      calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
      cvtColor(prevgray, cflow, CV_GRAY2BGR);
      drawOptFlowMap(flow, cflow, 16, 1.5, CV_RGB(0, 255, 0));
      imshow("flow", cflow);
    }
    std::swap(prevgray, gray);
  }
  return 0;
}
