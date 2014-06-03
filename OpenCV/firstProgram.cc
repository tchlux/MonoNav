// For macros and initialization protocols
//#include "cxtypes.h"
#include "cxmisc.h"
// For compiling computer vision related code
#include "cv.h"
#include "cxcore.h"
// For compiling machine learning related code
#include "highgui.h"
#include "ml.h"

using namespace std;

// This program is directly from the OpenCV textbook
int main(int argc, char * argv[]){
  IplImage* img = cvLoadImage( argv[1] );
  cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
  cvShowImage( "Example1", img );
  cvWaitKey(0);
  cvReleaseImage( &img );
  cvDestroyWindow( "Example1" );
  return(0);
}
