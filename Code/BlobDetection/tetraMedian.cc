#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector>

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"
#define TRACKBAR_WINDOW "Adjustable parameters"
#define ESC_KEY 1048603 // 27 Escape key on hp-elitebook
#define DEFAULT_IMAGE_SAMPLES 151
#define SAMPLE_COLOR Px(200,0,0)

#define MIN_LIFESPAN_TO_SHOW 5    // Min lifespan before valid
#define MAX_LIFESPAN_VALUE 255     // Max lifespan allowed
#define LIFESPAN_DECREMENT_RATE 10 // Rate at which it dies if not tracked

#define JUMP_TO_EDGE_COMPUTATIONS_PER_BLOB 16
#define STARTING_JUMP_SCALE 16 // Start distance for jumpToEdge of blobs
#define MIN_JUMP_SCALE 1 // The lowest jump allowed

#define POSITION_DYNAMIC_AVERAGE_BUFFER 4 //Position dynamic average buffer size
#define COLOR_DYNAMIC_AVERAGE_BUFFER 12 // Color dynamic average buffer size

#define VELOCITY_DIFFERENCE_THRESHOLD 15 // Max difference in velocity
#define POINT_DIFFERENCE_THRESHOLD 30 // How much points are allowed to differ
#define COLOR_DIFFERENCE_THRESHOLD 25 // How much pixel channels can differ

#define MAX_BLOBS_IN_OBJECT 20  // Max number of blobs in one object

#define BLOB_WIDTH(b) (b.upper.x-b.lower.x)
#define BLOB_HEIGHT(b) (b.upper.y-b.lower.y)
#define BLOB_CENTER(b) (Pt((b.lower.x+b.upper.x)/2,(b.lower.y+b.upper.y)/2))

class Blob;   // Holds details about a blob
class Object; // Holds many blobs that are of the same object
typedef cv::Mat Img; // "Img" for image
typedef cv::Vec3b Px; // "Px" for pixel 
typedef cv::Point Pt; // "Pt" for point
typedef cv::Point2f Velocity;
typedef std::vector<Blob> BlobVec;  // Vector of blobs
typedef BlobVec::iterator BlobIter; // ^^ iterator
typedef std::vector<Object> ObjVec; // Vector of objects
typedef ObjVec::iterator ObjIter;   // ^^ iterator

int g_position_dynamic_avg_buffer(POSITION_DYNAMIC_AVERAGE_BUFFER);
int g_color_difference_allowance(COLOR_DIFFERENCE_THRESHOLD);
int g_min_blob_dimension(10);// Minimum blob dimension allowed

// ===============================================
//      Runtime functions with no requirements    
// ===============================================

// Pre:  "toUpdate" and "newValue" are defined
// Post: The extrema values are stored in "toUpdate"
void setMin(int &toUpdate, const int &newValue){
  if (newValue < toUpdate)
    toUpdate = newValue;
}
void setMax(int &toUpdate, const int &newValue){
  if (newValue > toUpdate)
    toUpdate = newValue;
}

// Pre:  toUpdate and newPt are defined
// Post: The extrema values are stored in "toUpdate"
void setMinPt(Pt &toUpdate, const Pt &newPt){
  setMin(toUpdate.x, newPt.x);
  setMin(toUpdate.y, newPt.y);
}
void setMaxPt(Pt &toUpdate, const Pt &newPt){
  setMax(toUpdate.x, newPt.x);
  setMax(toUpdate.y, newPt.y);
}

// TODO:  This function returns the absolute difference between two values
// Pre:  "a" and "b" are defined and have comparison and subtraction operators
// Post: The positive difference of "a" and "b"
template <class T>
T difference(const T &a, const T &b){
  if (a > b)
    return (a-b);
  return (b-a);
}

// TODO:  This function compares the difference in x and y values of
//        two points to a threshold 
// Pre:  p1, p2 defined cvPoint types (either float or int)
// Post: True if ONE of the dimensional values is similar
template <class T>
bool xySimilar(const T &p1, const T &p2, int diffThresh){
  return (! ((difference(p1.x,p2.x) > diffThresh) &&
	     (difference(p1.y,p2.y) > diffThresh))  );
}

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

// Pre:  "toUpdate" and "newPoint" are defined
// Post: The dynamic average function is called on x and y values,
//	 changing "toUpdate" to be more similar to "newPoint"     
void updatePointAverage(Pt &toUpdate, const Pt &newPoint){
  updateAverage(toUpdate.x, newPoint.x, g_position_dynamic_avg_buffer);
  updateAverage(toUpdate.y, newPoint.y, g_position_dynamic_avg_buffer);
}

// Pre:  "toUpdate" and "newPoint" are defined
// Post: The dynamic average function is called on x and y values,
//	 changing "toUpdate" to be more similar to "newPoint"     
void updateVelocityAverage(Velocity &toUpdate, const Velocity &newVelocity){
  updateAverage(toUpdate.x, newVelocity.x, g_position_dynamic_avg_buffer);
  updateAverage(toUpdate.y, newVelocity.y, g_position_dynamic_avg_buffer);
}

// Pre:  "toUpdate" is defined as well as "newColor"
// Post: The dynamic average function is called on pixel channels,
//	 changing "toUpdate" to be more similar to "newColor"     
void updateColorAverage(Px &toUpdate, const Px &newColor){
  updateAverage(toUpdate[0], newColor[0], COLOR_DYNAMIC_AVERAGE_BUFFER);
  updateAverage(toUpdate[1], newColor[1], COLOR_DYNAMIC_AVERAGE_BUFFER);
  updateAverage(toUpdate[2], newColor[2], COLOR_DYNAMIC_AVERAGE_BUFFER);
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

// ====================
//      Blob Class     
// ====================

// Class: This struct holds information for a "blob" in an image, it
// uses a two-point bounding box, the blob's coor, and velocity as data
class Blob{
public:
  Pt lower;    // lower bound
  Pt upper;    // upper bound
  Px color;    // sample color of this blob
  Velocity velocity; // The blob's x and y velocity

  // Method:  Constructor given appropriate member data
  Blob(const Px &Color, const Pt &Lower, const Pt &Upper){
    color = Color;
    lower = Lower;
    upper = Upper;
    velocity = Velocity(0.0,0.0);
  }

  // Method: Constructor given another blob
  Blob(const Blob &b){
    color = b.color;
    lower = b.lower;
    upper = b.upper;
    velocity = b.velocity;
  }

  // Pre:  This blob is defined
  // Post: The predicted position based off current velocity is
  //       returned in the form of a new blob
  Blob prediction() const{
    const Pt newLower( (lower.x + (int) velocity.x),
		       (lower.y + (int) velocity.y) );
    const Pt newUpper( (upper.x + (int) velocity.x),
		       (upper.y + (int) velocity.y) );
    return Blob(color, newLower, newUpper);
  }
};

// ======================
//      Object Class     
// ======================

// Class: This class is designed to hold groupings of similar blobs,
// the natures of a tetraMedian search provides a grouped area where
// center points are usually found.  This class is used to contain all
// of the potential blob centers and provide a larger dataset for
// calculating relevant values (velocity, size, color, etc.)
class Object : public Blob{
public:
  BlobVec blobs;
  float velocityVariance;
  int lifespan;

  // Constructor: Given a blob, sets lifespan and stores blob
  Object(const Blob &blob):Blob(blob){
    lifespan = 1;
    blobs.push_back(blob);
  }

  // Pre:  "blob" is fully defined
  // Post: The velocity, color, and bounds of this object are updated
  void updateObject(const Blob &blob){
    updateVelocityAverage(velocity, blob.velocity);
    updateColorAverage(color, blob.color);
    setMinPt(lower, blob.lower);
    setMaxPt(upper, blob.upper);    
  }
};

// =============================================
//      Runtime Functions that require Blob     
// =============================================

// Pre:  box and currentBlob fully defined
// Post: true if "currentBlob" lies entirely inside of "box"
bool overlaps(const Blob &box, const Blob &currentBlob){
  const Pt center(BLOB_CENTER(currentBlob));
  return (((box.lower.x < center.x) &&
	   (box.lower.y < center.y)) &&
	  ((box.upper.x > center.x) &&
	   (box.upper.y > center.y)));
}

// Pre:  blob1 and blob2 are fully defined
// Post: True if two given blobs are similar to each other.  That
//       means that the colors are similar, the velocities are
//       similar, and the x OR y positions of BOTH lower and upper are
//       similar
bool blobsSimilar(const Blob &blob1, const Blob &blob2){
  return ( channelsSimilar(blob1.color, blob2.color) &&
	   xySimilar(blob1.velocity, blob2.velocity,
		     VELOCITY_DIFFERENCE_THRESHOLD) &&
	   xySimilar(blob1.lower, blob2.lower, POINT_DIFFERENCE_THRESHOLD) &&
	   xySimilar(blob1.upper, blob2.upper, POINT_DIFFERENCE_THRESHOLD));
}

// Pre:  "blob" is fully defined
// Post: true if the given blob's width OR height are too small
bool badBlobDimensions(const Blob &blob){
  return ((BLOB_WIDTH(blob) < g_min_blob_dimension) ||
	  (BLOB_HEIGHT(blob) < g_min_blob_dimension));    
}

// Pre:  "currentBlob" and "newPt" are fully defined
// Post: "newPt" is used to adjust the extrema of "currentBlob"
void adjustMinMax(Blob &currentBlob, const Pt &newPt){
  setMinPt(currentBlob.lower, newPt);
  setMaxPt(currentBlob.upper, newPt);
}

// ===========================
//      Tetramedian class     
// ===========================

// Class: This class provides the ability to sample an image with
// multiple evenly distributed "tetraMedian" searches for blobs.  It
// will produce a set of "Objects"
class TetraMedian{
public:
  int samples;
  int trackedBlobs;

  Img img;
  ObjVec objects;  

  // Constructor: Sets the number of samples
  TetraMedian(){
    samples = DEFAULT_IMAGE_SAMPLES;
    trackedBlobs = 0;
  }

  // ===============================
  //      Adding Blob operation     
  // ===============================

  // Pre:  "currentBlob" fully defined
  // Post: Cycles through all objects to check if it alligns with one
  //       of them (it is added if there's room otherwise dropped), if
  //       it is not similar to any current objects it is used to
  //       found a new object
  void addBlob(const Blob &currentBlob){
    bool added(false);      
    for (ObjIter obj(objects.begin()); ((obj < objects.end()) && !added); obj++){
      if (blobsSimilar((*obj), currentBlob)){
	added = true;
	if (obj->blobs.size() < MAX_BLOBS_IN_OBJECT){
	  obj->blobs.push_back(currentBlob);
	  trackedBlobs++;
	}
      }
    }
    if (!added && (trackedBlobs < samples)){
      objects.push_back(Object(currentBlob));
      trackedBlobs++;
    }
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
      if (!(inBounds(x, y) &&
	    channelsSimilar(blobColor, img.at<Px>(y, x)))){
	// If (not in bounds) or (channels differ)
	x -= (xMove*jumpScale); 
	y -= (yMove*jumpScale);
	jumpScale >>= 1; // Divide the jump amount by two
      }
    }
    return Pt(x,y);
  }

  // TODO:  This will perform the tetra median search assuming that
  //        start is the old blob position and end is where the new
  //        position will be stored.  
  //        It is assumed that:
  //         toUpdate.lower == toUpdate.upper == BLOB_CENTER(toUpdate)
  // Pre:  "toUpdate" is a fully defined blob where:
  //        lower == upper == BLOB_CENTER(toUpdate)
  // Post: The new extrema data of "toUpdate" for bounds are set after
  //       searching the current "img" for a center starting at
  //        "toUpdate"'s previous center point
  void tetraMedianSearch(Blob &toUpdate) const{
    Pt edge1(toUpdate.lower);    Pt edge2(toUpdate.lower);
    int  xDir(0);       int yDir(1);
    for (int i(0); i<JUMP_TO_EDGE_COMPUTATIONS_PER_BLOB; i+=2){
      const int x((edge1.x+edge2.x)/2);
      const int y((edge1.y+edge2.y)/2);
      edge1 = jumpToEdge(x, y, xDir, yDir, toUpdate.color);
      edge2 = jumpToEdge(x, y, -xDir, -yDir, toUpdate.color);
      setBiDirection8(xDir, yDir);
      // Update min and max
      adjustMinMax(toUpdate, edge1);
      adjustMinMax(toUpdate, edge2);
    }  
  }

  // Pre:  "blobToTrack" is fully defined
  // Post: A new blob search is started from the center of
  //       "blobToTrack", if the results of the search are similar to
  //        the blob then it is updated and true is returned,
  //        otherwise false is returned
  bool trackBlob(Blob &blobToTrack) const{
    const Pt previousCenter(BLOB_CENTER(blobToTrack));
    Blob newBlob(img.at<Px>(previousCenter.y, previousCenter.x), 
		 previousCenter, previousCenter);
    if (channelsSimilar(blobToTrack.color, newBlob.color)){
      tetraMedianSearch(newBlob);
      updatePointAverage(blobToTrack.lower, newBlob.lower);
      updatePointAverage(blobToTrack.upper, newBlob.upper);
      updateColorAverage(blobToTrack.color, newBlob.color);
      blobToTrack.velocity = (BLOB_CENTER(newBlob) - previousCenter);
      return true;
    }
    return false;
  }

  // Post: All objects that are similar to each other are merged, on
  //       the merge the farthest bounds are kept and the longest
  //       lifespan, the less significant object is erased.
  void mergeObjects(){
    const int halfSize = objects.size() / 2;
    for (ObjIter obj1(objects.begin()); obj1<objects.end(); obj1++){
      for (ObjIter obj2(obj1+1); obj2<objects.end();obj2++){
	if (blobsSimilar((*obj1), (*obj2))){ // If the two objects are similar
	  setMinPt(obj1->lower, obj2->lower); // Set the min of both objects
	  setMaxPt(obj1->upper, obj2->upper); // Set the max of both objects
	  setMax(obj1->lifespan, obj2->lifespan); // Take the larger lifespan
	  trackedBlobs -= obj2->blobs.size();
	  objects.erase(obj2); // Erase the now insignificant object
	}
      }
    }
  }

  // =============================
  //      Sampling operations     
  // =============================

  // Pre:  "obj" must be defined and prediction is the predicted next
  //       state of the object.
  // Post: Cycles through all blobs in "obj" performs a blob search
  //       from the previous center point, uses the new values to
  //       update the object or erase blobs from it if need be
  void reSampleObject(Object &obj, const Blob &prediction){
    obj.lower = obj.upper = BLOB_CENTER(obj); // Reset bounds of object
    for (BlobIter b(obj.blobs.begin()); b < obj.blobs.end(); b++){
      if (trackBlob(*b) && blobsSimilar(*b, prediction)){
	obj.updateObject(*b);
      }
      else{
	obj.blobs.erase(b);
	trackedBlobs--;
      }
    }    
  }

  // Pre:  numSamples > 0
  // Post: The samples are taken with an even distribution across the
  //       image, all blobs are added
  void sampleImgUniform(const int &numSamples){
    const int pixels(img.rows*img.cols);
    const int step(pixels / numSamples);
    for (int pixel(0); pixel<(pixels); pixel+=step){
      const Pt currentPoint(pixel%img.cols, pixel/img.cols);
      Blob currentBlob(img.at<Px>(currentPoint.y, currentPoint.x),
		       currentPoint, currentPoint);
      tetraMedianSearch(currentBlob);
      if (!badBlobDimensions(currentBlob))
	addBlob(currentBlob);    
      img.at<Px>(currentPoint.y, currentPoint.x) = SAMPLE_COLOR;
    }    
  }

  // ==============================================
  //      Primary blob detection function call     
  // ==============================================


  // Pre:  "obj" is fully defined
  // Post: First a prediction is established then the object is
  //       resampled according to the prediction.  If the object is
  //       empty then its lifespan is decremented and its member data
  //       is set to be that of the prediction (in hope that it will
  //       be rediscovered on another blob search) 
  //       false is returned "obj" is out of life and can no longer be tracked
  //       true is returned otherwise
  bool trackObject(Object &obj){
    if (obj.lifespan < MAX_LIFESPAN_VALUE)
      obj.lifespan++; // Increment the current running lifespan of this object

    const Blob prediction(obj.prediction());
    reSampleObject(obj, prediction);
    if (obj.blobs.empty()){
      if (obj.lifespan < MIN_LIFESPAN_TO_SHOW)
	return false;
      else{
	obj.lifespan -= LIFESPAN_DECREMENT_RATE;
	obj.color = prediction.color;
	obj.lower = prediction.lower;
	obj.upper = prediction.upper; 
	obj.velocity.x = obj.velocity.y = 0;
      }
    }
    return true;
  }

  // Post: If there are objects they are resampled first, then similar
  //       objects are merged together.  The remaining samples are
  //       spent uniformly across the image.
  void detectBlobs(){
    int objectSamples(0);
    for (ObjIter obj(objects.begin()); obj<objects.end(); obj++){	      
      if (! trackObject(*obj)){
	trackedBlobs -= obj->blobs.size();
	objects.erase(obj);
	// WARNING:  Erasing from the vector I'm cycling through    	
      }
      else
	objectSamples += obj->blobs.size();
    }
    mergeObjects();
    int regularSamples(samples - objectSamples);
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
    rectangle(outImg, blob.lower, blob.upper, 
	      cv::Scalar(blob.color[0], blob.color[1], blob.color[2]));
    const Pt center(BLOB_CENTER(blob.prediction()));
    cv::line(outImg, BLOB_CENTER(blob), center, velocityColor, 2);
  }

  // Pre:  "outImg" is the image that "obj" was gathered from, "obj" defined
  // Post: if "obj" has been alive for long enough it is drawn with
  //       the velocity vector color corresponding to the length of
  //       its life
  void drawObject(Img &outImg, const Object &obj){
    int life(obj.lifespan);
    setMin(life, MAX_LIFESPAN_VALUE);
    cv::Scalar velocityColor(life/2,life,0);
    if (life > MIN_LIFESPAN_TO_SHOW){
      drawBlob(outImg, obj, velocityColor);
    }
  }

  // Pre:  "outImg" is defined and the same as the one that
  //       "detectBlobs" was executed on
  // Post: Bounding boxes and vector lines for velocity are drawn for
  //       every single blob that has been discovered in the image
  void drawAllBlobs(Img &outImg){
    for (ObjIter obj(objects.begin()); obj<objects.end(); obj++){
      for (BlobIter b(obj->blobs.begin()); b<(obj->blobs.end()); b++){
	drawBlob(outImg, *b, cv::Scalar(0,200,0));
      }    
    }
  }

  // Pre:  "outImg" is defined, that is where the boxes are drawn
  // Post: A box is drawn marking the lower and upper bounds of every
  //       object, also a line is drawn at the center of the object
  //       marking its average vector velocity (color corresponding to lifespan)
  void drawAllObjects(Img &outImg){
    for (ObjIter obj(objects.begin()); obj<objects.end(); obj++){
      drawObject(outImg, *obj);
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
    cv::createTrackbar("Clear objects (1=true)", TRACKBAR_WINDOW,
    		       &clearObjects, 1);
    cv::createTrackbar("Color difference threshold", TRACKBAR_WINDOW,
		       &g_color_difference_allowance, (img.cols / 10));
    cv::createTrackbar("Position dynamic average buffer",
		       TRACKBAR_WINDOW, &g_position_dynamic_avg_buffer, 20);

    // Main test runs until user presses escape key
    while (cv::waitKey(1) != ESC_KEY){
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
      	img = cv::imread(argv[1]);
      }

      // Reset the blob image to black
      blobImg.setTo(cv::Scalar(0,0,0));
      // If the sliders are in valid positions then run the program
      detectBlobs(); // Build vectors of blobs in class
      drawAllBlobs(img); // Draw low level blob boundaries on original
      drawAllObjects(blobImg); // Draw high level boxes separately
      // Show both images to the user
      cv::imshow(ORIGINAL_IMAGE, img);
      cv::imshow(BLOBS_WINDOW, blobImg);

      // Clear the vector if requested to do so
      if (clearObjects){
	objects.clear();
	trackedBlobs = 0;
      }      
    }
  }

};
