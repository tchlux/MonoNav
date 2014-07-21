#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector>

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"
#define TRACKBAR_WINDOW "Adjustable parameters"
#define ESC_KEY 1048603 // 27 Escape key on hp-elitebook

#define SAMPLE_COLOR Px(200,0,0)   // The color all samples are drawn in
#define DEFAULT_IMAGE_SAMPLES 151  // Relative max computations done per frame

#define JUMP_TO_EDGE_COMPUTATIONS_PER_BLOB 16
#define STARTING_JUMP_SCALE 16 // Start distance for jumpToEdge of blobs
#define MIN_JUMP_SCALE 1 // The lowest jump allowed

#define POSITION_DYNAMIC_AVERAGE_BUFFER 4 //Position dynamic average buffer size
#define COLOR_DYNAMIC_AVERAGE_BUFFER 12 // Color dynamic average buffer size

#define VELOCITY_DIFFERENCE_THRESHOLD 15 // Max difference in velocity
#define POINT_DIFFERENCE_THRESHOLD 30 // How much points are allowed to differ
#define COLOR_DIFFERENCE_THRESHOLD 30 // How much pixel channels can differ

#define MAX_ACCELERATION Physics(10.0,10.0)

#define BLOB_WIDTH(b) (b.upper.pos.x-b.lower.pos.x)
#define BLOB_HEIGHT(b) (b.upper.pos.y-b.lower.pos.y)
#define BLOB_CENTER(b) (Pt((b.lower.pos.x+b.upper.pos.x)/2,(b.lower.pos.y+b.upper.pos.y)/2))

class Blob;   // Holds details about a blob
class Bound; // Holds a point and it's velocity for blob bound
typedef cv::Mat Img; // "Img" for image
typedef cv::Vec3b Px; // "Px" for pixel 
typedef cv::Point Pt; // "Pt" for point
typedef cv::Point2f Physics;
typedef std::vector<Blob> BlobVec;  // Vector of blobs
typedef BlobVec::iterator BlobIter; // ^^ iterator

// Globals for adjusting performance
int g_color_difference_allowance(COLOR_DIFFERENCE_THRESHOLD);
int g_position_difference_allowance(POINT_DIFFERENCE_THRESHOLD);
int g_min_blob_dimension(10);// Minimum blob dimension allowed

// ===============================================
//      Runtime functions with no requirements    
// ===============================================

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

template <class T>
// Pre:  toUpdate and newPt are defined
// Post: The extrema values are stored in "toUpdate"
void setMinXY(T &toUpdate, const T &newPt){
  setMin(toUpdate.x, newPt.x);
  setMin(toUpdate.y, newPt.y);
};
template <class T>
void setMaxXY(T &toUpdate, const T &newPt){
  setMax(toUpdate.x, newPt.x);
  setMax(toUpdate.y, newPt.y);
};

// Pre:  "toUpdate" and "newValue" defined with "+=" "-" and "/" operators
// Post: "toUpdate" is made more similar to "newValue" by a divided
//        factor of "setSize", the positive difference is used to
//        ensure function with unsigned types
template <class T>
void updateAverage(T &toUpdate, const T &newValue, const int &setSize){  
  if (newValue > toUpdate)
    toUpdate += (newValue - toUpdate) / setSize;
  else
    toUpdate -= (toUpdate - newValue) / setSize;
}

// Pre:  "toUpdate" is defined as well as "newColor"
// Post: The dynamic average function is called on pixel channels,
//	 changing "toUpdate" to be more similar to "newColor"     
void updateColorAverage(Px &toUpdate, const Px &newColor){
  updateAverage(toUpdate[0], newColor[0], COLOR_DYNAMIC_AVERAGE_BUFFER);
  updateAverage(toUpdate[1], newColor[1], COLOR_DYNAMIC_AVERAGE_BUFFER);
  updateAverage(toUpdate[2], newColor[2], COLOR_DYNAMIC_AVERAGE_BUFFER);
}   

// TODO:  This function returns the absolute difference between two values
// Pre:  "a" and "b" are defined and have comparison and subtraction operators
// Post: The positive difference of "a" and "b"
template <class T>
T difference(const T &a, const T &b){
  if (a > b)
    return (a-b);
  return (b-a);
};

// Pre:  p1, p2 defined cvPoint types (either float or int)
// Post: True if ONE of the dimensional values is similar
template <class T>
bool xySimilar(const T &p1, const T &p2, int diffThresh){
  return (! ((difference(p1.x,p2.x) > diffThresh) &&
	     (difference(p1.y,p2.y) > diffThresh))  );
};

// Pre:  "px1", "px2", g_color_difference_allowance defined, pixels have three channels
// Post: false if the positive difference in pixel values for any ONE
//       channel exceed "g_color_difference_allowance"
bool channelsSimilar(const Px &px1, const Px &px2){
  if ((difference(px1[0],px2[0]) > g_color_difference_allowance) ||
      (difference(px1[1],px2[1]) > g_color_difference_allowance) ||
      (difference(px1[2],px2[2]) > g_color_difference_allowance))
    return false;
  return true;
}

// Pre:  xDir and yDir defined, only one of them is non-zero
// Post: The next direction to travel (horizontal / vertical switch),
//       this is the set of logic gates for the search operation
void setBiDirection8(int &xDir, int &yDir){
  if ((yDir == 1) && (xDir == 0)){
    yDir = 0;
    xDir = 1;
  }  else if ((yDir == 0) && (xDir == 1)){
    yDir = -1;
    xDir = 1;
  }  else if ((yDir == -1) && (xDir == 1)){
    yDir = 1;
  }  else if ((yDir == 1) && (xDir == 1)){
    yDir = 1;
    xDir = 0;
  }
}


// =====================
//      Bound Class     
// =====================
class Bound{
public:
  Pt pos;
  Physics velocity;

  // TODO:  Constructor given position and velocity
  Bound(const int &x, const int &y, const Physics &vel) :
    pos(x,y), velocity(vel) {}

  // TODO:  Constructor given another Bound
  Bound(const Bound &bd) : pos(bd.pos), velocity(bd.velocity){}
};

// ====================
//      Blob Class     
// ====================

// Class: This struct holds information for a "blob" in an image, it
// uses a two-point bounding box, the blob's coor, and velocity as data
class Blob{
public:
  Bound lower;    // lower bound
  Bound upper;    // upper bound
  Px color;    // sample color of this blob

  // Method:  Constructor given appropriate member data
  Blob(const Px &Color, const Bound &Lower, const Bound &Upper) 
    : color(Color), lower(Lower), upper(Upper) {}

  // Method: Constructor given another blob
  Blob(const Blob &b)
    : color(b.color), lower(b.lower), upper(b.upper){ }
};

// =============================================
//      Runtime Functions that require Blob     
// =============================================

// Pre:  blob1 and blob2 are fully defined
// Post: True if two given blobs are similar to each other.  That
//       means that the colors are similar, the velocities are
//       similar, and the x OR y positions of BOTH lower and upper are
//       similar
bool blobsSimilar(const Blob &blob1, const Blob &blob2){
  return ( channelsSimilar(blob1.color, blob2.color) &&
	   xySimilar(blob1.lower.pos, blob2.lower.pos, 
		     g_position_difference_allowance) &&
	   xySimilar(blob1.upper.pos, blob2.upper.pos, 
		     g_position_difference_allowance));
}

// TODO:  This function updates a moving point with new data
void updateBound(Bound &toUpdate, const Bound &newPt){
  const Physics currentVelocity(newPt.pos.x - toUpdate.pos.x,
				newPt.pos.y - toUpdate.pos.y);
  Physics currentAcceleration(currentVelocity - toUpdate.velocity);

  setMinXY(currentAcceleration, MAX_ACCELERATION);
  setMaxXY(currentAcceleration, -MAX_ACCELERATION);

  toUpdate.velocity += currentAcceleration;
  toUpdate.pos.x += toUpdate.velocity.x;
  toUpdate.pos.y += toUpdate.velocity.y;
}

// TODO:  This function updates the stats of a blob
void updateBlob(Blob &toUpdate, const Blob &newBlob){
  updateColorAverage(toUpdate.color, newBlob.color);      
  updateBound(toUpdate.lower, newBlob.lower);
  updateBound(toUpdate.upper, newBlob.upper);
}

// Pre:  "blob" is fully defined
// Post: true if the given blob's width OR height are too small
bool badBlobDimensions(const Blob &blob){
  return ((BLOB_WIDTH(blob) < g_min_blob_dimension) ||
	  (BLOB_HEIGHT(blob) < g_min_blob_dimension));    
}

// ===========================
//      Tetramedian class     
// ===========================

// Class: This class provides the ability to sample an image with
// multiple evenly distributed "tetraMedian" searches for blobs.
class TetraMedian{
public:
  int samples;
  int trackedBlobs;

  Img img;
  BlobVec blobs;

  // Constructor: Sets the number of samples
  TetraMedian(){
    samples = DEFAULT_IMAGE_SAMPLES;
    trackedBlobs = 0;
  }

  // =================================
  //      Image Search Operations     
  // =================================

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
  Pt jumpToEdge(int x, int y, const int &xMove, const int &yMove,
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
    return Pt(x,y);
  }

  // Pre:  lower == upper, this is the start point for the search
  // Post: lower and upper are now the blob bounds for "color" from
  //       the given start point 
  void tetraMedianSearch(Pt &lower, Pt &upper, const Px &color) const{
    Pt edge1(lower);    Pt edge2(lower);
    int  xDir(0);       int yDir(1);
    for (int i(0); i<JUMP_TO_EDGE_COMPUTATIONS_PER_BLOB; i+=2){
      const int x((edge1.x+edge2.x)/2);
      const int y((edge1.y+edge2.y)/2);
      edge1 = jumpToEdge(x, y, xDir, yDir, color);
      edge2 = jumpToEdge(x, y, -xDir, -yDir, color);
      setBiDirection8(xDir, yDir);
      // Update min and max
      setMinXY(lower, edge1);      setMinXY(lower, edge2);
      setMaxXY(upper, edge1);      setMaxXY(upper, edge2);
    }  
  }

  // =============================
  //      Sampling operations     
  // =============================

  // Pre:  "currentBlob" fully defined
  // Post: Cycles through all objects to check if it alligns with one
  //       of them (it is added if there's room otherwise dropped), if
  //       it is not similar to any current objects it is used to
  //       found a new object
  void addBlob(const Blob &currentBlob){
    bool exists(false);      
    for (BlobIter b(blobs.begin()); b < blobs.end(); b++){
      exists = blobsSimilar((*b), currentBlob);
      if (exists)
	break;
    }
    if (!exists && (trackedBlobs < samples)){
      blobs.push_back(currentBlob);
      trackedBlobs++;
    }
  }

  // Pre:  numSamples > 0
  // Post: The samples are taken with an even distribution across the
  //       image, all blobs are added
  void sampleImgUniform(const int &numSamples){
    const int pixels(img.rows*img.cols);
    const int step(pixels / numSamples);
    for (int pixel(0); pixel<(pixels); pixel+=step){
      const Bound currentPoint(pixel%img.cols, pixel/img.cols, Physics(0.0,0.0));
      Blob currentBlob(img.at<Px>(currentPoint.pos.y, currentPoint.pos.x),
		       currentPoint, currentPoint);
      tetraMedianSearch(currentBlob.lower.pos, 
			currentBlob.upper.pos, 
			currentBlob.color);
      if (!badBlobDimensions(currentBlob))
	addBlob(currentBlob);
    }    
  }

  // Pre:  "blobToTrack" is fully defined
  // Post: A new blob search is started from the center of
  //       "blobToTrack", if the results of the search are similar to
  //        the blob then it is updated and true is returned,
  //        otherwise false is returned
  bool trackBlob(Blob &blobToTrack) const{
    Bound newLower(blobToTrack.lower.pos.x +
		   blobToTrack.lower.velocity.x,
		   blobToTrack.lower.pos.y +
		   blobToTrack.lower.velocity.y, blobToTrack.lower.velocity);
    Bound newUpper(blobToTrack.upper.pos.x +
		   blobToTrack.upper.velocity.x,
		   blobToTrack.upper.pos.y +
		   blobToTrack.upper.velocity.y, blobToTrack.upper.velocity);
    Bound center((newLower.pos.x+newUpper.pos.x)/2,
		 (newLower.pos.y+newUpper.pos.y)/2,
		 Physics((newLower.velocity.x+newUpper.velocity.x)/2,
			 (newLower.velocity.y+newLower.velocity.y)/2));
    Blob newBlob(img.at<Px>(center.pos.y,center.pos.x), center,center);
    // If the color is the same (still tracking right blob)
    if (channelsSimilar(blobToTrack.color, newBlob.color)){
      tetraMedianSearch(newBlob.lower.pos, newBlob.upper.pos, newBlob.color);
      updateBlob(blobToTrack, newBlob); // Update this blob
      return true;
    }
    return false;
  }

  // Post: If there are objects they are resampled first, then similar
  //       objects are merged together.  The remaining samples are
  //       spent uniformly across the image.
  void detectBlobs(){
    for (BlobIter b(blobs.begin()); b<blobs.end(); b++){	      
      if (!trackBlob(*b)){
	blobs.erase(b);
	trackedBlobs--;
      }
    }
    int regularSamples(samples - trackedBlobs);
    if (regularSamples > 0)
      sampleImgUniform(regularSamples);
  }

  // =========================
  //      Drawing methods     
  // =========================

  // Pre:  "outImg" is the image "blob" was gathered from, "blob" defined
  // Post: The bounds of "blob" are drawn into "outImg" and the
  //       velocity of "blob" is drawn as a vector line at its center
  //       with the color "velocityColor"
  void drawBlob(Img &outImg, const Blob &blob, 
		const cv::Scalar &velocityColor){
    rectangle(outImg, blob.lower.pos, blob.upper.pos, 
	      cv::Scalar(blob.color[0], blob.color[1], blob.color[2]));
    const Physics vel((blob.lower.velocity.x+blob.upper.velocity.x)/2,
		      (blob.lower.velocity.y+blob.upper.velocity.y)/2);
    const Pt center(BLOB_CENTER(blob));
    const Pt nextCenter(center.x+vel.x, center.y+vel.y);
    cv::line(outImg, center, nextCenter, velocityColor, 2);
  }

  // Pre:  "outImg" is defined and the same as the one that
  //       "detectBlobs" was executed on
  // Post: Bounding boxes and vector lines for velocity are drawn for
  //       every single blob that has been discovered in the image
  void drawAllBlobs(Img &outImg){
    for (BlobIter b(blobs.begin()); b<(blobs.end()); b++){
      drawBlob(outImg, *b, cv::Scalar(0,200,0));
    }    
  }

  // ====================================
  //      Testing and debugging code     
  // ====================================

  // TODO:  This method is for testing the blob detector
  void test(int argc, char *argv[]){
    // Initialize variables, the video from the webcam needs to be flipped
    Img temp; int clearObjects(0);
    cv::VideoCapture vid(0);
    vid >> temp;  cv::flip(temp, img, 1);
    if (argc == 2){
      vid.open(argv[1]);      
      vid >> img;
    }
    if (argc >= 3)
      img = cv::imread(argv[1]);
    Img blobImg(img.clone());

    // Initialize windows and create trackbars for runtime adjustments
    cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
    //    cv::setMouseCallback(ORIGINAL_IMAGE, onMouse);
    cv::waitKey(50);
    cv::namedWindow(TRACKBAR_WINDOW, CV_WINDOW_NORMAL);
    cv::waitKey(50);
    cv::namedWindow(BLOBS_WINDOW, CV_WINDOW_NORMAL);

    cv::createTrackbar("Samples", TRACKBAR_WINDOW, &samples, 
		       (img.rows*img.cols) / 512);
    cv::createTrackbar("Color difference threshold", TRACKBAR_WINDOW,
		       &g_color_difference_allowance, 128);
    cv::createTrackbar("Position difference threshold", TRACKBAR_WINDOW,
		       &g_position_difference_allowance, (img.cols / 10));
    cv::createTrackbar("Clear objects (1=true)", TRACKBAR_WINDOW,
		       &clearObjects, 1);

    // Main test runs until user presses escape key
    while (cv::waitKey(1) != ESC_KEY){
      // Clear the vector if requested to do so
      if (clearObjects){
	blobs.clear();
	trackedBlobs = 0; }      
      // Capture image for processing
      if (argc <= 2){
	if (argc == 2){
	  vid >> img;
	  if (img.empty()){
	    vid.release();
	    vid.open(argv[1]);
	    vid >> img; }}
	else{
	  vid >> temp;
	  cv::flip(temp, img, 1); }}
      else{
	img = cv::imread(argv[1]); }
      // Reset the blob image to black
      blobImg.setTo(cv::Scalar(0,0,0));
      // If the sliders are in valid positions then run the program
      detectBlobs(); // Build vectors of blobs in class
      drawAllBlobs(img); // Draw low level blob boundaries on original
      drawAllBlobs(blobImg); // Draw low level blob boundaries on original
      // Show both images to the user
      cv::imshow(ORIGINAL_IMAGE, img);
      cv::imshow(BLOBS_WINDOW, blobImg);
    }
  }

};
