#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"
#define TRACKBAR_WINDOW "Adjustable parameters"
#define ESC_KEY 27 //1048603 // Escape key on hp-elitebook

#define AVG_INC_AMOUNT 10 // The amount averages increment the green
// channel on derrivative images
#define BLUE cv::Vec3b(255,0,0)
#define RED cv::Vec3b(0,0,255)
#define GREEN cv::Vec3b(0,255,0)
#define BLOB_CENTER(y,x) blobImg.at<cv::Vec3b>(y,x)[1]
#define BLOB_HALF_WIDTH(y,x) blobImg.at<cv::Vec3b>(y,x)[0]
#define BLOB_HALF_HEIGHT(y,x) blobImg.at<cv::Vec3b>(y,x)[2]

#define DEFAULT_JUMP 16 // Default pixel jump when searching for boundaries
#define MIN_JUMP_SCALE 1 // Smallest scale allowed for ^^jumping
#define DEFAULT_DIFF_THRESH 25 // ~10% difference allowed before the
                               // current pixel is flagged as
                               // "differing" from the sample
                               // pixel. This is per-channel.

// TODO:  This is the class for blob detection
class TetraMedian{
public:
  typedef cv::Mat Img; // "Img" for image
  typedef cv::Vec3b Px; // "Px" for pixel 
  typedef cv::Point Pt; // "Pt" for point
  
  int dynamicAvgBufferSize;
  int blobCenterIncrement;
  int channelDiffThresh;
  int startingJumpScale;
  int drawBlobThresh;  
  int computations;
  int minJumpScale;
  int bImgRatio;

  int step;

  Img img;
  Img blobImg;

  TetraMedian(){
    dynamicAvgBufferSize = 2;
    blobCenterIncrement = 20;
    channelDiffThresh = 25;
    startingJumpScale = 16;
    drawBlobThresh = 200;
    computations = 16;
    minJumpScale = 1;
    bImgRatio = 1;
    step = 1;
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

  // TODO:  This function checks to see if the new edge points are
  //        relative min's and max's for this blob
  void updateMinMax(int &xMin, int &yMin, int &xMax, int &yMax,
		    const Pt &edge1, const Pt & edge2){
    setMin(xMin, edge1.x);    setMin(xMin, edge2.x);
    setMin(yMin, edge1.y);    setMin(yMin, edge2.y);
    setMax(xMax, edge1.x);    setMax(xMax, edge2.x);
    setMax(yMax, edge1.y);    setMax(yMax, edge2.y);
  }

  // Pre:  img, x, y are all defined
  // Post: true if the x,y coordinates are in the range of the image
  bool inBounds(const int &x, const int &y){
    return (((y >= 0) && (x >= 0)) &&
	    ((y < img.rows) && (x < img.cols)));
  }

  // Pre:  px1, px2, maxChannelDiff defined
  // Post: true if the SQUARED difference in pixel values for any ONE
  //       channel exceed "maxChannelDiff"
  bool channelsDiff(const Px &px1, const Px &px2){
    if (((px1[0]-px2[0]) > channelDiffThresh) || 
	((px2[0]-px1[0]) > channelDiffThresh) ||
	((px1[1]-px2[1]) > channelDiffThresh) || 
	((px2[1]-px1[1]) > channelDiffThresh) ||
	((px1[2]-px2[2]) > channelDiffThresh) || 
	((px2[2]-px1[2]) > channelDiffThresh))
      return true;
    return false;
  }

  // Pre:  img, x, y , xMove, yMove all defined, optional initial
  //       startingJumpScale and maxChannelDiff.
  // Post: The farthest point in the (x,y) direction specified that
  //       does NOT differ by more than "maxChannelDiff" on any ONE of
  //       the channels in the pixel, so color matters. The edge of
  //       the image is returned if it is reached.
  Pt jumpToEdge(int x, int y,
		const int &xMove, const int &yMove,
		const Px &blobColor){
    int jumpScale = startingJumpScale;
    while (jumpScale >= minJumpScale){
      x += (xMove*jumpScale); y += (yMove*jumpScale);
      if (!inBounds(x, y) ||
	  channelsDiff(blobColor, img.at<Px>(y, x))){
	// If (not in bounds) or (channels differ)
	x -= (xMove*jumpScale); y -= (yMove*jumpScale);
	jumpScale >>= 1; // Divide the jump amount by two
      }
    }
    return Pt(x,y);
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
  }

  // Pre:  all values given have been defined
  // Post: All values given are divided by bImgRatio, translating them
  //       to "blob image" coordinates
  void applyRatio(float &xAvg, float &yAvg, int &xMin, int &yMin,
		  int &xMax, int &yMax){
    xAvg /= bImgRatio;   yMax /= bImgRatio;
    yAvg /= bImgRatio;   xMin /= bImgRatio;
    xMax /= bImgRatio;   yMin /= bImgRatio;
  }

  // Pre:  Given values defined and within bounds of blobImg
  // Post: The blob information stored in the pixel location
  //       "(xAvg,yAvg)" is updated with the newest dimensions
  void updateBlob(const int &xAvg, const int &yAvg,
		  const int &xHalfRange, const int &yHalfRange){
    BLOB_HALF_WIDTH(yAvg,xAvg) += 
      ((xHalfRange-BLOB_HALF_WIDTH(yAvg,xAvg))/dynamicAvgBufferSize);
    BLOB_HALF_HEIGHT(yAvg,xAvg) += 
      ((yHalfRange-BLOB_HALF_HEIGHT(yAvg,xAvg))/dynamicAvgBufferSize);
    BLOB_CENTER(yAvg,xAvg) += blobCenterIncrement;
  }

  // TODO:  Draws a rectangle around a "blob" if it exceeds a threshold
  void  drawBlobBounds(const int &xAvg, const int &yAvg){
    if (BLOB_CENTER(yAvg,xAvg) >= drawBlobThresh){
      Pt minCorner(xAvg-BLOB_HALF_WIDTH(yAvg,xAvg),
		   yAvg-BLOB_HALF_HEIGHT(yAvg,xAvg));
      Pt maxCorner(xAvg+BLOB_HALF_WIDTH(yAvg,xAvg),
		   yAvg+BLOB_HALF_HEIGHT(yAvg,xAvg));
      rectangle(blobImg, minCorner, maxCorner, cv::Scalar(255,0,0));
      rectangle(img, minCorner*bImgRatio, maxCorner*bImgRatio, cv::Scalar(255,0,0));
    }
  } 

  // TODO:  This will do a successive median point search for the
  //        'center' of the blob that search point comes from
  void biDirection8(const int &col, const int &row){
    const Px blobColor(img.at<Px>(row, col));
    float xAvg(col); float yAvg(row); 
    int   xMin(col);   int yMin(row);
    int   xMax(col);   int yMax(row);
    int   xDir(0);     int yDir(-1);
    Pt edge1(col,row);
    Pt edge2(col,row);
    for (int i(0); i<computations; i+=2){
      const int x((edge1.x+edge2.x)/2);
      const int y((edge1.y+edge2.y)/2);
      edge1 = jumpToEdge(x, y, xDir, yDir, blobColor);
      setBiDirection8(xDir, yDir);
      edge2 = jumpToEdge(x, y, xDir, yDir, blobColor);
      setBiDirection8(xDir, yDir);
      // Dynamically calculate average
      xAvg += (x-xAvg) / dynamicAvgBufferSize;
      yAvg += (y-yAvg) / dynamicAvgBufferSize;
      // Update min and max
      updateMinMax(xMin, yMin, xMax, yMax, edge1, edge2);
    }  
    applyRatio(xAvg, yAvg, xMin, yMin, xMax, yMax);
    updateBlob(xAvg, yAvg, (xMax-xMin)/2, (yMax-yMin)/2);
    drawBlobBounds(xAvg, yAvg);

  }

  // TODO:  This will run the blob detection algorithm, all parameters
  //        must have been set before calling this method
  void detectBlobs(){
    for (int col(step); col<(img.cols-1); col+=step){
      for (int row(step); row<(img.rows-1); row+=step){
	biDirection8(col, row);
      }
    }
  }

//////////////////////////////////////////////////////////////////////
  // ====================================
  //      Testing and debugging code     
  // ====================================
//////////////////////////////////////////////////////////////////////

  // TODO:  Prints all member data to the terminal
  void printMemberData(){
    std::cerr << "dynamicAvgBufferSize: " << dynamicAvgBufferSize << std::endl;
    std::cerr << "blobCenterIncrement: " << blobCenterIncrement << std::endl;
    std::cerr << "channelDiffThresh: " << channelDiffThresh << std::endl;
    std::cerr << "startingJumpScale: " << startingJumpScale << std::endl;
    std::cerr << "drawBlobThresh: " << drawBlobThresh << std::endl;
    std::cerr << "computations: " << computations << std::endl;
    std::cerr << "minJumpScale: " << minJumpScale << std::endl;
    std::cerr << "bImgRatio: " << bImgRatio << std::endl;
    std::cerr << "step: " << step << std::endl;    
    std::cerr << "img.rows: " << img.rows << std::endl;
    std::cerr << "img.cols: " << img.cols << std::endl;
    std::cerr << "blobImg.rows: " << blobImg.rows << std::endl;
    std::cerr << "blobImg.cols: " << blobImg.cols << std::endl;
  }

  // TODO:  This initializes cv trackbars and windows for testing
  void initCV(){
    cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
    cv::waitKey(50);
    cv::namedWindow(BLOBS_WINDOW, CV_WINDOW_NORMAL);
    cv::waitKey(50);
    cv::namedWindow(TRACKBAR_WINDOW, CV_WINDOW_NORMAL);

    cv::createTrackbar("Step", TRACKBAR_WINDOW, &step, 
		       (img.cols+img.rows)/4+1);
    cv::createTrackbar("Computations", TRACKBAR_WINDOW, 
		       &computations, 100);
    cv::createTrackbar("Channel Diff Threshold", TRACKBAR_WINDOW, 
		       &channelDiffThresh, 100);
    cv::createTrackbar("Dynamic Buffer Size", TRACKBAR_WINDOW, 
		       &dynamicAvgBufferSize, 10);
    cv::createTrackbar("Blob Image reduction ratio", TRACKBAR_WINDOW, 
		       &bImgRatio, 6);
    cv::createTrackbar("Blob Average Increment", TRACKBAR_WINDOW,
		       &blobCenterIncrement, 125);
    cv::createTrackbar("Draw blob threshold", TRACKBAR_WINDOW,
		       &drawBlobThresh, 255);
  }

  // TODO:  This method is for testing the blob detector
  void test(int argc, char *argv[]){
    cv::VideoCapture vid(0);
    vid >> img;
    if (argc >= 2)
      img = cv::imread(argv[1]);

    step = (img.cols+img.rows)/80;
    computations = 16;
    bImgRatio = 1;
    img.copyTo(blobImg);
    initCV();
    while (cv::waitKey(1) != ESC_KEY){

      blobImg.setTo(cv::Scalar(0,0,0)); 
      if ((img.rows / blobImg.rows) != bImgRatio)
	blobImg.reshape(0, img.rows/bImgRatio);
      if (argc < 2)
	vid >> img;
      else
	img = cv::imread(argv[1]);

      detectBlobs();
      cv::imshow(ORIGINAL_IMAGE, img);
      cv::imshow(BLOBS_WINDOW, blobImg);
    }
  }

};
