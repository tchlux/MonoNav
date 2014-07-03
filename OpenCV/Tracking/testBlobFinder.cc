#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>
#include "Derriv.cc"

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"
#define TRACKBAR_WINDOW "Adjustable parameters"

#define AVG_OCCUR 3 // The max number of occurances
                    // of an average that can be
                    // stored in one byte
#define AVG_INC_AMOUNT (255/AVG_OCCUR) // The amount averages increment the green
                                       // channel on derrivative images
#define BLUE cv::Vec3b(255,0,0)
#define RED cv::Vec3b(0,0,255)
#define GREEN cv::Vec3b(0,255,0)
#define BLOB_CENTER(img,y,x) img.at<cv::Vec3b>(y,x)[1]
#define BLOB_HALF_WIDTH(img,y,x) img.at<cv::Vec3b>(y,x)[0]
#define BLOB_HALF_HEIGHT(img,y,x) img.at<cv::Vec3b>(y,x)[2]

#define ESC_KEY 27 //1048603 // Escape key on hp-elitebook
#define DEFAULT_JUMP 16 // Default pixel jump
#define MIN_JUMP_SCALE 1 // Smallest scale allowed
#define DEFAULT_DIFF_THRESH 25 // (~10% difference allowed)

int g_diff_thresh(DEFAULT_DIFF_THRESH); // Channel difference allowed
int g_frac(2); // Fractional favor towards later-collected points for
	       // the biDirection functions

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
  if (((px1[0]-px2[0]) > maxChannelDiff) || ((px2[0]-px1[0]) > maxChannelDiff) ||
      ((px1[1]-px2[1]) > maxChannelDiff) || ((px2[1]-px1[1]) > maxChannelDiff) ||
      ((px1[2]-px2[2]) > maxChannelDiff) || ((px2[2]-px1[2]) > maxChannelDiff))
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
  while (jumpScale >= MIN_JUMP_SCALE){
    x += (xMove*jumpScale); y += (yMove*jumpScale);
    if (!inBounds(img, x, y) ||
	(channelsDiff(blobColor, img.at<px>(y, x), g_diff_thresh))){
      // If (not in bounds) or (channels differ)
      x -= (xMove*jumpScale); y -= (yMove*jumpScale);
      jumpScale >>= 1; // Divide the jump amount by two
    }
  }
  return cv::Point(x,y);
}

// Pre:  xDir and yDir defined, only one of them is non-zero
// Post: The next direction to travel (horizontal / vertical switch)
void setBiDirection8(int &xDir, int &yDir){
  if ((yDir == -1) && (xDir == 0)){
    yDir = 1;
  }
  else if ((yDir == 1) && (xDir == 0)){
    yDir = 0;
    xDir = 1;
  }
  else if ((yDir == 0) && (xDir == 1)){
    xDir = -1;
  }
  else if ((yDir == 0) && (xDir == -1)){
    yDir = -1;
    xDir = 1;
  }
  else if ((yDir == -1) && (xDir == 1)){
    yDir = 1;
    xDir = -1;
  }
  else if ((yDir == 1) && (xDir == -1)){    
    xDir = 1;
  }
  else if ((yDir == 1) && (xDir == 1)){
    yDir = -1;
    xDir = -1;
  }
  else if ((yDir == -1) && (xDir == -1)){
    yDir = -1;
    xDir = 0;
  }
  else
    std::cerr << "setBiDirection8 logic crash." 
	      << std::endl;
}

// TODO:  This Function updates the blob information at a certain
//        pixel location. Encoding "width" and "height" into the pixel
//        blue and red channels respectively
void updateBlob(cv::Mat &outImg, const int &xAvg, const int &yAvg,
		const int &xHalfRange, const int &yHalfRange){
  const int count(outImg.at<px>(yAvg,xAvg)[1] / AVG_INC_AMOUNT);
  BLOB_HALF_WIDTH(outImg,yAvg,xAvg) += 
    (xHalfRange-BLOB_HALF_WIDTH(outImg,yAvg,xAvg))/AVG_OCCUR;
  BLOB_HALF_HEIGHT(outImg,yAvg,xAvg) += 
    (yHalfRange-BLOB_HALF_HEIGHT(outImg,yAvg,xAvg))/AVG_OCCUR;
  BLOB_CENTER(outImg,yAvg,xAvg) += AVG_INC_AMOUNT;
}


// Pre:  a and be are defined
// Post: The extrema values are stored in a
void setMin(int &a, const int &b){
  if (b < a)
    a = b;
}
void setMax(int &a, const int &b){
  if (b > a)
    a = b;
}

// TODO:  This will do a successive biian point search for the
//        'center' of the blob that search point comes from
void biDirection8(cv::Mat &inImg, cv::Mat &outImg,
		  const int &col, const int &row, const int &computations){
  const px blobColor(inImg.at<px>(row, col));
  float xAvg(col); float yAvg(row); 
  int   xMin(col);   int yMin(row);
  int   xMax(col);   int yMax(row);
  int   xDir(0);     int yDir(-1);
  cv::Point edge1(col,row);
  cv::Point edge2(col,row);
  outImg.at<px>(row,col) = BLUE;
  for (int i(0); i<computations; i+=2){
    const int x((edge1.x+edge2.x)/2);
    const int y((edge1.y+edge2.y)/2);
    edge1 = jumpToEdge(inImg, x, y, xDir, yDir, blobColor);
    setBiDirection8(xDir, yDir);
    edge2 = jumpToEdge(inImg, x, y, xDir, yDir, blobColor);
    setBiDirection8(xDir, yDir);
    // Dynamically calculate average
    xAvg += (x-xAvg) / g_frac;
    yAvg += (y-yAvg) / g_frac;
    // Update min and max
    setMin(xMin, edge1.x);    setMin(xMin, edge2.x);
    setMin(yMin, edge1.y);    setMin(yMin, edge2.y);
    setMax(xMax, edge1.x);    setMax(xMax, edge2.x);
    setMax(yMax, edge1.y);    setMax(yMax, edge2.y);
    outImg.at<px>(edge1.y,edge1.x) = RED;
    outImg.at<px>(edge2.y,edge2.x) = RED;
  }  
  updateBlob(outImg, xAvg, yAvg, (xMax-xMin)/2, (yMax-yMin)/2);
  if (BLOB_CENTER(outImg,yAvg,xAvg) >= 250){
    cv::Point minCorner(xAvg-BLOB_HALF_WIDTH(outImg,yAvg,xAvg),
			yAvg-BLOB_HALF_HEIGHT(outImg,yAvg,xAvg));
    cv::Point maxCorner(xAvg+BLOB_HALF_WIDTH(outImg,yAvg,xAvg),
			yAvg+BLOB_HALF_HEIGHT(outImg,yAvg,xAvg));
    rectangle(inImg, minCorner, maxCorner, cv::Scalar(255,0,0));
  }
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
  int step(((img.cols+img.rows)/4)/20);
  int computations(16);

  cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
  cv::namedWindow(BLOBS_WINDOW, CV_WINDOW_NORMAL);
  cv::namedWindow(TRACKBAR_WINDOW, CV_WINDOW_NORMAL);

  cv::createTrackbar("Step", TRACKBAR_WINDOW, &step, 
  		     (img.cols+img.rows)/4+1, callbackDummy);
  cv::createTrackbar("Computations", TRACKBAR_WINDOW, &computations, 
		     100, callbackDummy);
  cv::createTrackbar("Threshold", TRACKBAR_WINDOW, &g_diff_thresh,
		     100, callbackDummy);
  cv::createTrackbar("Avg Favor", TRACKBAR_WINDOW, &g_frac,
		     10, callbackDummy);

  while (cv::waitKey(1) != ESC_KEY){
    if (argc < 2)
      vid >> img;
    else
      img = cv::imread(argv[1]);
    // img.copyTo(imgDerriv);
    imgDerriv.setTo(cv::Scalar(0,0,0));
    for (int col(step); col<(img.cols-1); col+=step){
      for (int row(step); row<(img.rows-1); row+=step){
    	  biDirection8(img, imgDerriv, col, row, computations);
      }
    }
    cv::imshow(ORIGINAL_IMAGE, img);
    cv::imshow(BLOBS_WINDOW, imgDerriv);
  }
  return 0;
}

    // vid >> img;
    // if (img.rows < 1){
    //   vid.open(argv[1]);
    //   vid >> img;
    // }
