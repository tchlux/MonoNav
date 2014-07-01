#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>
#include "Derriv.cc"

#define BLOBS_WINDOW "BLOBS SON"
#define ORIGINAL_IMAGE "Original Image"
#define ESC_KEY 1048603 // Escape key on hp-elitebook
#define DEFAULT_JUMP 5 // Default pixel jump
#define MIN_JUMP_SCALE 1 // Smallest scale allowed
#define DEFAULT_DIFF_THRESH 650
// 20*20 (~8% difference allowed)

typedef cv::Vec3b px; // "px" for pixel 

// Used for an unnecessary callback, no function
void callbackDummy(int,void*){}

// Pre:  img, x, y are all defined
// Post: true if the x,y coordinates are in the range of the image
bool inBounds(const cv::Mat &img, const int &x, const int &y){
  return (((y >= 0) && (x >= 0)) &&
	  ((y < img.rows) && (x < img.cols)));
}

// Pre:  px1, px2, maxChannelDiff defined
// Post: true if the SQUARED difference in pixel values for any ONE
//       channel exceed "maxChannelDiff"
bool channelsDiff(const px &px1, const px &px2, 
		  const int &maxChannelDiff=DEFAULT_DIFF_THRESH){
  if (((px1[0]-px2[0])*(px1[0]-px2[0]) > maxChannelDiff) ||
      ((px1[1]-px2[1])*(px1[1]-px2[1]) > maxChannelDiff) ||
      ((px1[2]-px2[2])*(px1[2]-px2[2]) > maxChannelDiff))
    return true;
  return false;
}

// Pre:  img, x, y , xMove, yMove all defined, optional initial
//       jumpScale and maxChannelDiff.
// Post: The farthest point in the (x,y) direction specified that
//       does NOT differ by more than "maxChannelDiff" on any ONE of
//       the channels in the pixel, so color matters. The edge of
//       the image is returned if it is reached.
cv::Point jumpToEdge(const cv::Mat &img, int x, int y,
		     const int &xMove, const int &yMove,
		     const px &blobColor,
		     int jumpScale=DEFAULT_JUMP, 
		     const int &maxChannelDiff=DEFAULT_DIFF_THRESH){
  x += (xMove*jumpScale);
  y += (yMove*jumpScale);
  while (jumpScale >= MIN_JUMP_SCALE){
    if (inBounds(img, x, y) &&
	(! channelsDiff(blobColor, img.at<px>(y, x), maxChannelDiff))){
      x += (xMove*jumpScale); y += (yMove*jumpScale);
    }
    else{
      // Subtract out the old jump
      x -= (xMove*jumpScale); y -= (yMove*jumpScale);
      // Divide the jump amount by two
      jumpScale >>= 1;
      // Add the new half jump
      x += (xMove*jumpScale); y += (yMove*jumpScale);      
    }
  }
  return cv::Point(x,y);
}

// TODO:  This function will set the new direction of travel based off
//        of the old direction of travel. Cycling through possible points
void setDirection(int &xDir, int &yDir){
  if (yDir == -1){
    yDir = 0;  xDir = 1;
  }
  else if (xDir == 1){
    yDir = 1;  xDir = 0;
  }
  else if (yDir == 1){
    yDir = 0;  xDir = -1;
  }
  else{
    yDir = -1; xDir = 0;
  } 
}

// TODO:  This function will identify the blob surrounding the given
//        pixel and place an outline around it in the outImage
void blobFinder(const cv::Mat &inImg, cv::Mat &outImg,
		const int &col, const int &row, const int &depth){
  const px blobColor(inImg.at<px>(row, col));
  float ptsFound(1);  
  float avgX(col);
  float avgY(row);
  int xDir(0);
  int yDir(-1);
  cv::Point edge(row,col);
  outImg.at<px>(row,col) = px(0,255,0);

  for (int i(0); i<depth; i++){
    edge = jumpToEdge(inImg, edge.x, edge.y, xDir, yDir, blobColor);
    setDirection(xDir, yDir);
    // Dynamically calculate average
    ptsFound++;
    avgX = avgX*((ptsFound-1)/ptsFound) + edge.x/ptsFound;
    avgY = avgY*((ptsFound-1)/ptsFound) + edge.y/ptsFound;
    outImg.at<px>(edge.y,edge.x) = px(255,0,0);
  }
  outImg.at<px>(avgY,avgX) = px(0,0,255);
}

// TODO:  This function will provide testing ground for the vector
//        based image derrivative
int main(int argc, char *argv[]){
  cv::VideoCapture vid(0);
  cv::Mat img; // Open the image provided
  vid >> img;
  if (argc >= 2)
    img = cv::imread(argv[1]);

  cv::Mat imgDerriv(img.clone());

  cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
  cv::namedWindow(BLOBS_WINDOW, CV_WINDOW_NORMAL);

  while (cv::waitKey(1) != ESC_KEY){
    if (argc < 2)
      vid >> img;
    img.copyTo(imgDerriv);
    blobFinder(img, imgDerriv, img.cols/2, img.rows/2, 10);
    // for (int col(10); col<img.cols; col+=50){
    //   for (int row(10); row<img.rows; row+=50){
    // 	blobFinder(img, imgDerriv, col, row, 100);
    //   }
    // }
    cv::imshow(ORIGINAL_IMAGE, img);
    cv::imshow(BLOBS_WINDOW, imgDerriv);
  }
  return 0;
}
