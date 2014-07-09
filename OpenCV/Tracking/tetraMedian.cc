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

class Blob;

typedef cv::Mat Img; // "Img" for image
typedef cv::Vec3b Px; // "Px" for pixel 
typedef cv::Point Pt; // "Pt" for point
typedef std::vector<Blob> BlobVec;
typedef BlobVec::iterator BlobIter;


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
  int computations;
  int minJumpScale;
  int clearBlobs;
  int maxBlobs;
  int samples;

  Img img;
  BlobVec blobs;

  TetraMedian(){
    dynamicAvgBufferSize = 3;
    channelDiffThresh = 25;
    startingJumpScale = 16;
    minBlobDimension = 15;
    drawBlobThresh = 2;
    computations = 16;
    minJumpScale = 1;
    clearBlobs = 1;
    maxBlobs = 20;
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

  // Pre:  box and currentBlob fully defined
  // Post: true if the center of "currentBlob" lies within the
  //       boundaries of "box"
  bool overlaps(const Blob &box, const Blob &currentBlob){
    return (((box.lower.x < currentBlob.center.x) &&
	     (box.lower.y < currentBlob.center.y)) &&
	    ((box.upper.x > currentBlob.center.x) &&
	     (box.upper.y > currentBlob.center.y)));
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

  // Pre:  toUpdate and newData fully defined
  // Post: The member data of "toUpdate" is updated with the member
  //       data of "newData" using the dynamic average function
  void updateBlob(Blob &toUpdate, Blob &newData){
    // Update center and dimensions of blob
    toUpdate.center.x += 
      (newData.center.x - toUpdate.center.x) / dynamicAvgBufferSize;
    toUpdate.center.y += 
      (newData.center.y - toUpdate.center.y) / dynamicAvgBufferSize;

    toUpdate.lower.x += 
      (newData.lower.x - toUpdate.lower.x) / dynamicAvgBufferSize;
    toUpdate.lower.y += 
      (newData.lower.y - toUpdate.lower.y) / dynamicAvgBufferSize;

    toUpdate.upper.x += 
      (newData.upper.x - toUpdate.upper.x) / dynamicAvgBufferSize;
    toUpdate.upper.y += 
      (newData.upper.y - toUpdate.upper.y) / dynamicAvgBufferSize;
    // Increment occurance
    toUpdate.occurance ++;
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

  // TODO:  This function will add the blob to a vector, it is the
  //        most complex operation of the entire process
  void addBlob(Blob &currentBlob){
    bool needToAdd(true);
    BlobIter position(blobs.begin());
    for (int b(0); b<blobs.size(); b++){
      if ((blobs[b].upper.x-blobs[b].lower.x < minBlobDimension) ||
	  (blobs[b].upper.y-blobs[b].lower.y < minBlobDimension))
	blobs.erase(blobs.begin() + b);
      if (overlaps(blobs[b], currentBlob)){
	if (!channelsDiff(blobs[b].color, currentBlob.color)){
	  needToAdd = false;
	  updateBlob(blobs[b], currentBlob);
	  break;
	}
	else{
	  blobs.erase(blobs.begin() + b);
	}
      }
    }
    if ((blobs.size() < maxBlobs) &&
	(needToAdd) &&
	((currentBlob.upper.x-currentBlob.lower.x > minBlobDimension) &&
	 (currentBlob.upper.y-currentBlob.lower.y > minBlobDimension))){
      blobs.push_back(currentBlob);
    }      

  }

  // Pre:  col and row are within the bounds of "img"
  // Post: Four different sloped lines are projected outwards starting
  //        from "col" and "row" in "img" and the median point of the
  //        "jumpToEdge" searches for both directions on that line is
  //        used as the starting point for the searches on the next
  //        line.  This is done with "computations" calls to the
  //        "jumpToEdge" function and finally produces one "center" of
  //        a blob
  void biDirection8(const int &col, const int &row){
    Blob currentBlob(img.at<Px>(row,col), col, row);
    int  xDir(0);       int yDir(-1);
    Pt edge1(col,row);  Pt edge2(col,row);
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

  // Pre:  numSamples > 0
  // Post: The samples are evenly distributed across the image
  void sampleImgUniform(const int &numSamples){
    const int pixels(img.rows*img.cols);
    const int step(pixels / numSamples);
    for (int pixel(step); pixel<(pixels); pixel+=step){
      biDirection8(pixel%img.cols, pixel/img.rows);
    }    
  }

  // TODO:  This will run the blob detection algorithm, all parameters
  //        must have been set before calling this method
  void detectBlobs(Img &inImg, BlobVec &inOut){
    int regularSamples(samples);

    if (blobs.size() > 0){
      for (int b(0); b < blobs.size(); b++){
	biDirection8(blobs[b].center.x-1, blobs[b].center.y);
	biDirection8(blobs[b].center.x+1, blobs[b].center.y);
	biDirection8(blobs[b].center.x, blobs[b].center.y-1);
	biDirection8(blobs[b].center.x, blobs[b].center.y+1);
      }
      regularSamples -= blobs.size();
    }

    if (regularSamples > 0){
      sampleImgUniform(regularSamples);
    }
}
  
  // Pre:  outImg is of the same dimensions as the image used to
  //         calculate all of the points stored in "blobs"
  // Post: outImg is marked with blue rectangles marking the bounds of
  //         the blobs stored in "blobs"
  void drawBlobBounds(Img &outImg){
    for (int b(0); b<blobs.size(); b++){
      if (blobs[b].occurance >= drawBlobThresh){
	rectangle(outImg, blobs[b].lower, blobs[b].upper, 
		  cv::Scalar(blobs[b].color[0],
			     blobs[b].color[1],
			     blobs[b].color[2]));
      }
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

    cv::createTrackbar("Channel Diff Threshold", TRACKBAR_WINDOW, 
		       &channelDiffThresh, 127);
    cv::createTrackbar("Dynamic Buffer Size", TRACKBAR_WINDOW, 
		       &dynamicAvgBufferSize, 16);
    cv::createTrackbar("Computations", TRACKBAR_WINDOW, 
		       &computations, 80);
    cv::createTrackbar("Samples", TRACKBAR_WINDOW, &samples, 
		       (img.rows*img.cols) / 512);
    cv::createTrackbar("Max Blobs", TRACKBAR_WINDOW, &maxBlobs, 
    		       (img.rows*img.cols) / 512);
    cv::createTrackbar("Minimum blob dimension", TRACKBAR_WINDOW,
		       &minBlobDimension, img.rows / 2);
    cv::createTrackbar("Draw blob threshold", TRACKBAR_WINDOW,
		       &drawBlobThresh, 200);
    cv::createTrackbar("Clear blobs (1=true)", TRACKBAR_WINDOW,
		       &clearBlobs, 1);

    while (cv::waitKey(1) != ESC_KEY){
      if (argc < 2)
	vid >> img;
      else
	img = cv::imread(argv[1]);

      if ((samples > 0) &&
	  (dynamicAvgBufferSize > 0))
      	detectBlobs(img, blobs);

      drawBlobBounds(img);
      cv::imshow(ORIGINAL_IMAGE, img);
      if (clearBlobs)
	blobs.clear();
    }
  }

};

