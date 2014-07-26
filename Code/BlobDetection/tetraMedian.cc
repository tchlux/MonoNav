#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector> // For holding a set of blobs

#define DEFAULT_IMAGE_SAMPLES 151  // Number of uniform sample points gathered

#define JUMP_TO_EDGE_COMPUTATIONS_PER_BLOB 16 // Two passes over a
                                              // tetra median search
#define STARTING_JUMP_SCALE 16 // Starting scale for jumpToEdge of blobs
#define MIN_JUMP_SCALE 1 // The lowest jump allowed (finest scale of
                         // travel direction traversed across image

#define COLOR_DYNAMIC_AVERAGE_BUFFER 8 // Color dynamic average buffer size
#define COLOR_DIFFERENCE_THRESHOLD 30 // How much pixel channels can differ
#define POINT_DIFFERENCE_THRESHOLD 30 // How much points are allowed to differ

#define VELOCITY_DIFFERENCE_THRESHOLD 10 // Max difference in velocity
                                         // to be declared similar
#define MAX_ACCELERATION 9.8f // Maximum floating point acceleration
                              // per dimension

#define MIN_BLOB_DIMENSION 10 // Smallest blob width/height allowed

#define BLOB_WIDTH(b) (b.upper.x-b.lower.x)
#define BLOB_HEIGHT(b) (b.upper.y-b.lower.y)
#define BLOB_CENTER(b) cv::Point((b.lower.x+b.upper.x)/2, \
                                 (b.lower.y+b.upper.y)/2)


class Blob;   // Holds two points and two velocities
typedef cv::Vec3b Px; // "Px" for pixel 
typedef cv::Point IntPt; // "IntPt" for integer ponit
typedef std::vector<Blob> BlobVec;  // Vector of blobs
typedef BlobVec::iterator BlobIter; // ^^ iterator

// ===========================
//      Template Utilities    
// ===========================

// Pre:  "toUpdate" and "newValue" are defined
// Post: The extrema values are stored in "toUpdate"
template <class T>
void setMin(T &toUpdate, const T &newValue){
  if (newValue < toUpdate)
    toUpdate = newValue;
};
template <class T>
void setMax(T &toUpdate, const T &newValue){
  if (newValue > toUpdate)
    toUpdate = newValue;
};

// Pre:  "a" and "b" are defined and have comparison and subtraction operators
// Post: The positive difference of "a" and "b"
template <class T>
T difference(const T &a, const T &b){
  if (a > b)
    return (a-b);
  return (b-a);
};

// Pre:  "toUpdate" and "newValue" defined with "+=" "-" and "/" operators
// Post: "toUpdate" is made more similar to "newValue" by a divided
//        factor of "setSize", the positive difference is used to
//        ensure function with unsigned types.  If "setSize" is the
//        current size of the set with newValue included this is a
//        dynamic averaging function
template <class T>
void updateAverage(T &toUpdate, const T &newValue, const int &setSize){  
  if (newValue > toUpdate)
    toUpdate += (newValue - toUpdate) / setSize;
  else
    toUpdate -= (toUpdate - newValue) / setSize;
}

// Pre:  p1, p2 defined cvPoint types (either float or int)
// Post: True if x AND y values are similar
template <class T>
bool xAndySimilar(const T &p1, const T &p2, int diffThresh){
  return ( (difference(p1.x,p2.x) < diffThresh) &&
           (difference(p1.y,p2.y) < diffThresh) );
};

// =========================
//      Pixel Utilities     
// =========================

// Pre:  "toUpdate" is defined as well as "newColor"
// Post: The dynamic average function is called on pixel channels,
//	 changing "toUpdate" to be more similar to "newColor"     
void updateColorAverage(Px &toUpdate, const Px &newColor){
  updateAverage(toUpdate[0], newColor[0], COLOR_DYNAMIC_AVERAGE_BUFFER);
  updateAverage(toUpdate[1], newColor[1], COLOR_DYNAMIC_AVERAGE_BUFFER);
  updateAverage(toUpdate[2], newColor[2], COLOR_DYNAMIC_AVERAGE_BUFFER);
}   

// Pre:  "px1", "px2", "COLOR_DIFFERENCE_THRESHOLD" defined, pixels
//       have three channels 
// Post: false if the positive difference in pixel values for any ONE
//       channel exceeds "COLOR_DIFFERENCE_THRESHOLD"
bool channelsSimilar(const Px &px1, const Px &px2){
  if ((difference(px1[0],px2[0]) > COLOR_DIFFERENCE_THRESHOLD) ||
      (difference(px1[1],px2[1]) > COLOR_DIFFERENCE_THRESHOLD) ||
      (difference(px1[2],px2[2]) > COLOR_DIFFERENCE_THRESHOLD))
    return false;
  return true;
}

// ========================
//      Search Utility     
// ========================

// Pre:  xDir and yDir defined, only one of them is non-zero
// Post: The next direction to travel (horizontal / vertical switch),
//       this is the set of logic gates for a tetra median search
//       operation.
void setSearchDirection(int &xDir, int &yDir){
  if ((yDir == 1) && (xDir == 0)){ // If North South
    yDir = 0; // Make East West
    xDir = 1;
  }  else if ((yDir == 0) && (xDir == 1)){ // If East West
    yDir = -1; // Make Northeast Southwest
    xDir = 1;
  }  else if ((yDir == -1) && (xDir == 1)){ // If Northeast Southwest
    yDir = 1; // Make Northwest Southeast
  }  else if ((yDir == 1) && (xDir == 1)){ // If Northwest Southeast
    yDir = 1; // Make North South
    xDir = 0;
  }
}

// ====================
//      Blob Class     
// ====================

// Class: This struct holds information for a "blob" in an image, it
// uses a two-point bounding box, the blob's color, and velocities of
// the bounding corners as member data
class Blob{
public:
  Px color;    // sample color of this blob
  IntPt lower;
  IntPt upper;

  // Method:  Constructor given appropriate member data
  Blob(const Px &Color, const IntPt &Lower, const IntPt &Upper) 
    : color(Color), lower(Lower), upper(Upper) {}

  // Method: Constructor given another blob
  Blob(const Blob &b)
    : color(b.color), lower(b.lower), upper(b.upper) {}
};

// =============================================
//      Runtime Functions that require Blob     
// =============================================

// Pre:  "blob" is fully defined
// Post: true if the given blob's width OR height are too small
bool badBlobDimensions(const Blob &blob){
  return ( (BLOB_WIDTH(blob)  < MIN_BLOB_DIMENSION) ||
           (BLOB_HEIGHT(blob) < MIN_BLOB_DIMENSION) );    
}

// Pre:  blob1 and blob2 are fully defined
// Post: True if two given blobs are similar to each other. Defined:
//       All channels of colors are similar, 
//       xOrySimilar for lower AND upper
bool blobsSimilar(const Blob &blob1, const Blob &blob2){
  return ( channelsSimilar(blob1.color, blob2.color) &&
	   (xAndySimilar(blob1.lower, blob2.lower,
			 POINT_DIFFERENCE_THRESHOLD) ||
	    xAndySimilar(blob1.upper, blob2.upper,
			 POINT_DIFFERENCE_THRESHOLD)) );
}

// =========================
//      Drawing methods     
// =========================

// Pre:  "outImg" is defined and is of the same dimensions as the one
//       that "detectBlobs" was executed on
// Post: Bounding boxes and vector lines for velocity are drawn for
//       every single blob that has been discovered in the image
void drawBlobs(cv::Mat &outImg, BlobVec &blobs, const int minLife=0){
  for (BlobIter b(blobs.begin()); b<(blobs.end()); b++){
    rectangle(outImg, b->lower, b->upper, 
	      cv::Scalar(b->color[0], b->color[1], b->color[2]));
  }    
}

// ===============================
//      RecursiveMedian class     
// ===============================

// Class: This class provides the ability to sample uniformly 
// and an image and perform
// multiple evenly distributed "recursiveMedian" searches for blobs.
class RecursiveMedian{
public:
  int samples;
  cv::Mat img; // The Mat class just copies the header so this will
               // not be computationally cumbersome

  // Constructor: Sets the number of samples
  RecursiveMedian() : samples(DEFAULT_IMAGE_SAMPLES) {}

  // ============================================
  //      Recursive Median Search Operations     
  // ============================================

  // Pre:  img, x, y are all defined
  // Post: true if the x,y coordinates are in the range of the image
  bool inBounds(const int &x, const int &y) const{
    return (((y >= 0) && (x >= 0)) &&
	    ((y < img.rows) && (x < img.cols)));
  }

  // Pre:  img, x, y , xMove, yMove, blobColor all defined
  // Post: The farthest point from (x,y) in the vector (xMove,yMove)
  //       direction specified that does NOT differ by more than
  //       "maxChannelDiff" on any ONE of the channels in the pixel,
  //       so color matters. The edge of the image is returned if it is reached.
  IntPt jumpToEdge(int x, int y, const int &xMove, const int &yMove,
		const Px &blobColor) const{
    int jumpScale = STARTING_JUMP_SCALE;
    while (jumpScale >= MIN_JUMP_SCALE){
      x += (xMove*jumpScale); 
      y += (yMove*jumpScale);
      if (!(inBounds(x, y) && channelsSimilar(blobColor, img.at<Px>(y, x)))){
	// If (not in bounds) or (channels differ)
	x -= (xMove*jumpScale); 
	y -= (yMove*jumpScale);
	jumpScale >>= 1; // Divide the jump amount by two
      }
    }
    return IntPt(x,y);
  }

  // Pre:  lower == upper, this is the start point for the search
  // Post: lower and upper are now the blob bounds for "color" from
  //       the given start point 
  void recursiveMedianSearch(IntPt &lower, IntPt &upper, const Px &color) const{
    IntPt edge1(lower);    IntPt edge2(upper);
    int  xDir(0);       int yDir(1);
    for (int i(0); i<JUMP_TO_EDGE_COMPUTATIONS_PER_BLOB; i+=2){
      const int x((edge1.x+edge2.x)/2);
      const int y((edge1.y+edge2.y)/2);
      edge1 = jumpToEdge(x, y, xDir, yDir, color);
      edge2 = jumpToEdge(x, y, -xDir, -yDir, color);
      setSearchDirection(xDir, yDir);
      // Update min and max
      setMin(lower.x, edge1.x); setMin(lower.y, edge1.y);
      setMin(lower.x, edge2.x); setMin(lower.y, edge2.y);
      setMax(upper.x, edge1.x); setMax(upper.y, edge1.y);
      setMax(upper.x, edge2.x); setMax(upper.y, edge2.y);
    }  
  }

  // ==========================================
  //      Image Sampling and Blob Addition     
  // ==========================================

  // Pre:  "currentBlob" fully defined
  // Post: Cycles through all objects to check if it alligns with one
  //       of them (it is added if there's room otherwise dropped), if
  //       it is not similar to any current objects it is used to
  //       found a new object
  void addBlob(const Blob &currentBlob, BlobVec &blobs){
    bool exists(false);      
    for (BlobIter b(blobs.begin()); b < blobs.end(); b++){
      exists = blobsSimilar((*b), currentBlob);
      if (exists){
	updateColorAverage(b->color, currentBlob.color);
	setMin(b->lower.x, currentBlob.lower.x);
	setMin(b->lower.y, currentBlob.lower.y);
	setMax(b->upper.x, currentBlob.upper.x);
	setMax(b->upper.y, currentBlob.upper.y);
	break;
      }
    }
    if (!exists)
      blobs.push_back(currentBlob);
  }

  // Pre:  numSamples > 0
  // Post: The samples are taken with an even distribution across the
  //       image, all blobs of passing proportions are added to blobs
  void sampleImgUniform(const int &numSamples, BlobVec &blobs){
    const int pixels(img.rows*img.cols);
    const int step(pixels / numSamples);
    for (int pixel(0); pixel<(pixels); pixel+=step){
      const IntPt currentPoint(pixel%img.cols, pixel/img.cols);
      Blob currentBlob(img.at<Px>(currentPoint.y, currentPoint.x),
		       currentPoint, currentPoint);
      recursiveMedianSearch(currentBlob.lower, 
			    currentBlob.upper, 
			    currentBlob.color);
      if (!badBlobDimensions(currentBlob))
	addBlob(currentBlob, blobs);
    }    
  }

  // Pre:  image and blobs are defined
  // Post: If there are blobs they are resampled first.  The remaining
  //       samples are spent uniformly across the image.
  void detect(const cv::Mat &image, BlobVec &blobs){
    img = image; // reference to image stored for simplicity
    for (BlobIter b(blobs.begin()); b<blobs.end(); b++){	      
      b->lower = b->upper = BLOB_CENTER((*b));
      recursiveMedianSearch(b->lower, b->upper, b->color);
    }
    int regularSamples(samples - blobs.size());
    if (regularSamples > 0)
      sampleImgUniform(regularSamples, blobs);
  }
};
