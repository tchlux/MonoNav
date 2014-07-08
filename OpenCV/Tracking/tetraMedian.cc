#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector>
#include <assert.h>

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"
#define TRACKBAR_WINDOW "Adjustable parameters"
#define ESC_KEY 1048603 //27 // Escape key on hp-elitebook

#define BLOB_HEIGHT(blob) blob.upper.y-blob.lower.y
#define BLOB_WIDTH(blob) blob.upper.x-blob.lower.x

typedef cv::Mat Img; // "Img" for image
typedef cv::Vec3b Px; // "Px" for pixel 
typedef cv::Point Pt; // "Pt" for point

#define SQRT_PRECISION 1.0 // The minimal accuracy of the square root

// Pre:  0 < num, 0 < precision
// Post: The approximate square root of num to a set digit accuracy
float sqrt(float num){
  bool flipped = num < 1.0; // if less than one, needs to be flipped
  if (flipped) num = 1.0 / num; // Make the number > 1
  float last = 1.0;  float guess = 2.0;
  float diff = (num-guess*guess);
  while ( diff*diff > SQRT_PRECISION){
    if (guess*guess < num){
      last = guess;
      guess = (guess+num)/2;
    }
    else
      guess = (guess+last)/2;
    diff = (num-guess*guess);
  }
  if (flipped) guess = 1.0 / guess; // flip back if necessary
  return(guess);                                                                       }

// TODO:  This class will hold the information for a blob
class Blob{
public:
  Px color;
  Pt lower;
  Pt upper;
  Pt center;
  int occurance;

  // Default constructor
  Blob(const Px Color, const int Col, const int Row){
    color = Color;
    lower = Pt(Col,Row);
    upper = Pt(Col,Row);
    center = Pt(Col,Row);
    occurance = 1;
  }
};

// TODO:  This is the class for blob detection
class TetraMedian{
public:
  
  int dynamicAvgBufferSize;
  int channelDiffThresh;
  int startingJumpScale;
  int minBlobDimension;
  int drawBlobThresh;
  int blobSampleBox;
  int computations;
  int minJumpScale;
  int clearBlobs;
  int samples;

  Img img;
  std::vector<Blob> blobs;

  TetraMedian(){
    dynamicAvgBufferSize = 2;
    channelDiffThresh = 25;
    startingJumpScale = 16;
    minBlobDimension = 20;
    drawBlobThresh = 1;
    blobSampleBox = 2;
    computations = 16;
    minJumpScale = 1;
    clearBlobs = 1;
    samples = 100;
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
  void updateMinMax(Blob &currentBlob, const Pt &edge1, const Pt & edge2){
    setMin(currentBlob.lower.x, edge1.x);
    setMin(currentBlob.lower.x, edge2.x);
    setMin(currentBlob.lower.y, edge1.y);
    setMin(currentBlob.lower.y, edge2.y);
    setMax(currentBlob.upper.x, edge1.x);
    setMax(currentBlob.upper.x, edge2.x);
    setMax(currentBlob.upper.y, edge1.y);
    setMax(currentBlob.upper.y, edge2.y);
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

  // TODO:  This method determines whether or not a given set of
  //         dimensions overlaps with a blob at "position" in a vector
  bool overlaps(const Blob &otherBlob, const Blob &currentBlob){
    return (((otherBlob.lower.x < currentBlob.center.x) &&
	     (otherBlob.lower.y < currentBlob.center.y)) &&
	    ((otherBlob.upper.x > currentBlob.center.x) &&
	     (otherBlob.upper.y > currentBlob.center.y)));
  }

  // TODO:  This function updates the information of the blab at the
  //         given "position" in blobs
  void updateBlob(Blob &otherBlob, Blob &currentBlob){
    // Update center and dimensions of blob
    otherBlob.center.x += 
      (currentBlob.center.x - otherBlob.center.x) / dynamicAvgBufferSize;
    otherBlob.center.y += 
      (currentBlob.center.y - otherBlob.center.y) / dynamicAvgBufferSize;

    otherBlob.lower.x += 
      (currentBlob.lower.x - otherBlob.lower.x) / dynamicAvgBufferSize;
    otherBlob.lower.y += 
      (currentBlob.lower.y - otherBlob.lower.y) / dynamicAvgBufferSize;

    otherBlob.upper.x += 
      (currentBlob.upper.x - otherBlob.upper.x) / dynamicAvgBufferSize;
    otherBlob.upper.y += 
      (currentBlob.upper.y - otherBlob.upper.y) / dynamicAvgBufferSize;
    // Increment occurance
    otherBlob.occurance ++;
  }

  // TODO:  This function will add the blob to a vector, it is the
  //        most complex operation of the entire process
  void addBlob(Blob &currentBlob){
    bool needToAdd(true);
    std::vector<Blob>::iterator position(blobs.begin());
    for (; position<blobs.end(); position++){
      if (overlaps(*position, currentBlob)){
	needToAdd = false;
	updateBlob(*position, currentBlob);
	if ((position->upper.x-position->lower.x < minBlobDimension) ||
	    (position->upper.y-position->lower.y < minBlobDimension))
	  blobs.erase(position);
	break;
      }
    }
    if ((needToAdd) &&
	((currentBlob.upper.x-currentBlob.lower.x > minBlobDimension) &&
	 (currentBlob.upper.y-currentBlob.lower.y > minBlobDimension))){
      blobs.push_back(currentBlob);
    }      

  }

  // TODO:  This will do a successive median point search for the
  //        'center' of the blob that search point comes from
  void biDirection8(const int &col, const int &row){
    Blob currentBlob(img.at<Px>(row,col), col, row);
    int   xDir(0);     int yDir(-1);
    Pt edge1(col,row);    Pt edge2(col,row);
    for (int i(0); i<computations; i+=2){
      const int x((edge1.x+edge2.x)/2);
      const int y((edge1.y+edge2.y)/2);
      edge1 = jumpToEdge(x, y, xDir, yDir, currentBlob.color);
      setBiDirection8(xDir, yDir);
      edge2 = jumpToEdge(x, y, xDir, yDir, currentBlob.color);
      setBiDirection8(xDir, yDir);
      // Dynamically calculate average
      currentBlob.center.x += (x-currentBlob.center.x) / dynamicAvgBufferSize;
      currentBlob.center.y += (y-currentBlob.center.y) / dynamicAvgBufferSize;
      // Update min and max
      updateMinMax(currentBlob, edge1, edge2);
    }  
    addBlob(currentBlob);    
  }

  // TODO:  This function samples one single blob uniformly 
  void sampleBlob(const Blob &blob){
    int blobHeight = BLOB_HEIGHT(blob);
    int blobWidth = BLOB_WIDTH(blob);
    int rowStep(blobHeight / blobSampleBox);
    int colStep(blobWidth / blobSampleBox);
    std::cerr << "tetraMedian.cc Line 273: " << std::endl;
    if ((rowStep > 0) && (colStep > 0)){
      std::cerr << "blobHeight: " << blobHeight << std::endl;
      std::cerr << "blobWidth: " << blobWidth << std::endl;
      std::cerr << "blobSampleBox: " << blobSampleBox << std::endl;
      std::cerr << "rowStep: " << rowStep << std::endl;
      std::cerr << "colStep: " << colStep << std::endl;
      std::cerr << "blob.upper: " << blob.upper << std::endl;
      std::cerr << "blob.lower: " << blob.lower << std::endl;
      for (int row(blobHeight / (2*blobSampleBox));
	   row < blobHeight; row+=rowStep){
	for (int col(blobWidth / (2*blobSampleBox));
	     col < blobWidth; col+=colStep){
	  const int currCol(col+blob.lower.x);
	  const int currRow(row+blob.lower.y);
	  biDirection8(currCol, currRow);	
	}
      }
    }
    std::cerr << "tetraMedian.cc Line 284: " << std::endl;
  }

  // TODO:  This function will sample all current blobs
  int sampleBlobs(){
    int samplesTaken(0);
    std::cerr << "tetraMedian.cc Line 291: " << std::endl;
    for (std::vector<Blob>::iterator b(blobs.begin());
	 (b < blobs.end() && samplesTaken<(samples-1)); b++){
      sampleBlob(*b);
      samplesTaken++;
    }
    std::cerr << "tetraMedian.cc Line 296: " << std::endl;
    return samplesTaken*(blobSampleBox*blobSampleBox);
  }

  // TODO:  This will run the blob detection algorithm, all parameters
  //        must have been set before calling this method
  void detectBlobs(Img &inImg, std::vector<Blob> &inOut){
    img = inImg;
    blobs = inOut;
    sampleBlobs();
    int regularSamples(samples - blobs.size() * (blobSampleBox*blobSampleBox));
    int yStep(img.rows / sqrt((float) (regularSamples*img.cols)/img.rows));
    int xStep(img.cols / sqrt((float) (regularSamples*img.rows)/img.cols));
    for (int row(yStep); row<(img.rows); row+=yStep){
      for (int col(xStep); col<(img.cols); col+=xStep){
	biDirection8(col, row);
      }
    }
}
  
  // TODO:  This function will go through the vector of blobs and draw
  //         boxes around them
  void drawBlobBounds(Img &outImg){
    for (int b(0); b<blobs.size(); b++){
      if (blobs[b].occurance >= drawBlobThresh)
	rectangle(outImg, blobs[b].lower, blobs[b].upper, cv::Scalar(255,0,0));
    }
  }

//////////////////////////////////////////////////////////////////////
  // ====================================
  //      Testing and debugging code     
  // ====================================
//////////////////////////////////////////////////////////////////////


  // TODO:  This method is for testing the blob detector
  void test(int argc, char *argv[]){
    cv::VideoCapture vid(0);
    vid >> img;
    if (argc >= 2)
      img = cv::imread(argv[1]);

    cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
    cv::waitKey(50);
    cv::namedWindow(TRACKBAR_WINDOW, CV_WINDOW_NORMAL);

    cv::createTrackbar("Samples", TRACKBAR_WINDOW, &samples, 
		       (img.rows*img.cols) / 512);
    cv::createTrackbar("Computations", TRACKBAR_WINDOW, 
		       &computations, 80);
    cv::createTrackbar("Channel Diff Threshold", TRACKBAR_WINDOW, 
		       &channelDiffThresh, 127);
    cv::createTrackbar("Dynamic Buffer Size", TRACKBAR_WINDOW, 
		       &dynamicAvgBufferSize, 16);
    cv::createTrackbar("Draw blob threshold", TRACKBAR_WINDOW,
		       &drawBlobThresh, 200);
    cv::createTrackbar("Clear blobs (1=true)", TRACKBAR_WINDOW,
		       &clearBlobs, 1);
    cv::createTrackbar("Minimum blob dimension", TRACKBAR_WINDOW,
		       &minBlobDimension, img.rows / 2);

    while (cv::waitKey(1) != ESC_KEY){
      if (argc < 2)
	vid >> img;
      else
	img = cv::imread(argv[1]);

      if (samples > 0)
	detectBlobs(img, blobs);

      drawBlobBounds(img);
      cv::imshow(ORIGINAL_IMAGE, img);
      if (clearBlobs)
	blobs.clear();
    }
  }

};

