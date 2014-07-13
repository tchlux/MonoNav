#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector>

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"
#define TRACKBAR_WINDOW "Adjustable parameters"
#define ESC_KEY 1048603 // 27 Escape key on hp-elitebook
#define CHANNEL_DIFF_THRESH 25 // 10% channel difference
#define STARTING_JUMP_SCALE 16 // Start distance for jumping to edge
                               //  of blobs
#define MIN_JUMP_SCALE 1 // The lowest jump allowed
#define MAX_ALLOWED_COLOR_CHANGE 10 // Max color change allowed b
#define MAX_VELOCITY 5 // The maximum allowed velocity to be displayed
                       // for objects

#define BLOB_WIDTH(b) (b.upper.x-b.lower.x)
#define BLOB_HEIGHT(b) (b.upper.y-b.lower.y)
#define BLOB_CENTER(b) (Pt((b.lower.x+b.upper.x)/2,(b.lower.y+b.upper.y)/2))

class Blob;   // Holds details about a blob
class Object; // Holds many blobs that are of the same object
typedef cv::Mat Img; // "Img" for image
typedef cv::Vec3b Px; // "Px" for pixel 
typedef cv::Point Pt; // "Pt" for point
typedef std::vector<Blob> BlobVec;  // Vector of blobs
typedef BlobVec::iterator BlobIter; // ^^ iterator
typedef std::vector<Object> ObjVec; // Vector of objects
typedef ObjVec::iterator ObjIter;   // ^^ iterator

int g_pos_dab(3);    //Position dynamic average buffer size
int g_color_dab(9); // Color dynamic average buffer size
int g_point_diff_thresh(50); // How much points are allowed to differ
int g_min_blob_dimension(10); // Minimum blob dimension allowed
int g_max_blobs_in_object(10); // Max number of blobs in one object

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

// Pre:  p1 and p2 are defined fully
// Post: This function returns true if two points differ from each
//       other beyond "g_point_diff_thresh" on BOTH x and y
//       dimensions.  It will return false if ONE of the dimensions
//       has similar values.
bool pointsDiff(const Pt &p1, const Pt &p2){
  return ((((p1.x - p2.x) > g_point_diff_thresh) ||
	   ((p2.x - p1.x) > g_point_diff_thresh)) &&
	  (((p1.y - p2.y) > g_point_diff_thresh) ||
	   ((p2.y - p1.y) > g_point_diff_thresh)));
}

// Pre:  "a" and "b" are defined
// Post: The positive difference between the channels is returned
unsigned char channelDifference(const unsigned char a,
				const unsigned char b){
  if (a > b)
    return (a-b);
  return (b-a);
}

// TODO:  This function returns the sum of the positive differences
//        between all three channels of two pixels
int pixelDifference(const Px &px1, const Px &px2){
  return (channelDifference(px1[0],px2[0]) +
	  channelDifference(px1[1],px2[1]) + 
	  channelDifference(px1[2],px2[2]));
}

// Pre:  "px1", "px2", CHANNEL_DIFF_THRESH defined, pixels have three
//        channels
// Post: true if the SQUARED difference in pixel values for any ONE
//       channel exceed "maxChannelDiff"
bool channelsDiff(const Px &px1, const Px &px2){
  if ((channelDifference(px1[0],px2[0]) > CHANNEL_DIFF_THRESH) ||
      (channelDifference(px1[1],px2[1]) > CHANNEL_DIFF_THRESH) ||
      (channelDifference(px1[2],px2[2]) > CHANNEL_DIFF_THRESH))
    return true;
  return false;
}

// Pre:  "toUpdate" and "newPoint" are both defined fully
// Post: "toUpdate" is modified to be more similar to "newPoint", the
//       amount it is adjusted is deterimed by a combination of the
//       magnitude of the difference between "toUpdate" and "newPoint"
//       and the denominator (average contribution factor) of the
//       operation (see dynamic average explanation at top of file)
void updatePointAverage(Pt &toUpdate, const Pt &newPoint){
  toUpdate.x += (newPoint.x - toUpdate.x) / g_pos_dab;
  toUpdate.y += (newPoint.y - toUpdate.y) / g_pos_dab;
}

// Pre:  "toUpdate" and "newColor" are both defined fully
// Post: "toUpdate" is modified to be more similar to "newColor", the
//       amount it is adjusted is deterimed by a combination of the
//       magnitude of the difference between "toUpdate" and "newColor"
//       and the denominator (average contribution factor) of the
//       operation (see dynamic average explanation at top of file)
void updateColorAverage(Px &toUpdate, const Px &newColor){
  if (newColor[0] > toUpdate[0])
    toUpdate[0] += (newColor[0]-toUpdate[0]) / g_color_dab;
  else
    toUpdate[0] -= (toUpdate[0]-newColor[0]) / g_color_dab;
  if (newColor[1] > toUpdate[1])
    toUpdate[1] += (newColor[1]-toUpdate[1]) / g_color_dab;
  else
    toUpdate[1] -= (toUpdate[1]-newColor[1]) / g_color_dab;
  if (newColor[2] > toUpdate[2])
    toUpdate[2] += (newColor[2]-toUpdate[2]) / g_color_dab;
  else
    toUpdate[2] -= (toUpdate[2]-newColor[2]) / g_color_dab;
  // ^^ This covers the cases when one is larger than the other so
  // that overflow is not encountered
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

// TODO:  This class will hold the information for a blob
class Blob{
public:
  Px color;    // sample color of this blob
  Pt lower;    // lower bound
  Pt upper;    // upper bound
  Pt velocity; // The blob's x and y velocity

  // Method:  Constructor given appropriate member data
  Blob(const Px &Color, const Pt &Lower, const Pt &Upper){
    color = Color;
    lower = Lower;
    upper = Upper;
    velocity = Pt(0,0);
  }

  // Method: Constructor given another blob
  Blob(const Blob &b){
    color = b.color;
    lower = b.lower;
    upper = b.upper;
    velocity = b.velocity;
  }
};

// ======================
//      Object Class     
// ======================

class Object : public Blob{
public:
  BlobVec blobs;
  int lifespan;

  // TODO:  Constructor given valid blob
  Object(const Blob &blob):Blob(blob){
    lifespan = 1;
    blobs.push_back(blob);
  }

  // TODO:  This method updates the current object's member data with
  //        the given blob
  void updateObject(const Blob &blob){
    updatePointAverage(velocity, blob.velocity);
    updateColorAverage(color, blob.color);
    updatePointAverage(lower, blob.lower);
    updatePointAverage(upper, blob.upper);
    // setMinPt(lower, blob.lower);
    // setMaxPt(upper, blob.upper);    
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

// TODO:  This function returns true if two given blbos differ from
//        each other
bool blobsDiff(const Blob &blob1, const Blob &blob2){
  return ( channelsDiff(blob1.color, blob2.color) ||
	   (! (overlaps(blob1,blob2) || overlaps(blob2,blob1)) &&
	    (pointsDiff(blob1.lower, blob2.lower) || 
	     pointsDiff(blob1.upper, blob2.upper))) );
}

// TODO:  Returns true if the blob doesn't meet requirements
bool badBlobDimensions(const Blob &b){
  return ((BLOB_WIDTH(b) < g_min_blob_dimension) ||
	  (BLOB_HEIGHT(b) < g_min_blob_dimension));    
}

// TODO:  This function checks to see if "newPt" is a relative min or
//        maximum that should be stored in the current blob
void adjustMinMax(Blob &currentBlob, const Pt &newPt){
  setMinPt(currentBlob.lower, newPt);
  setMaxPt(currentBlob.upper, newPt);
}

// ===========================
//      Tetramedian class     
// ===========================

// TODO:  This is the class for blob detection
class TetraMedian{
public:
  int computations;
  int trackedBlobs;
  int samples;

  Img img;
  ObjVec objects;

  TetraMedian(){
    computations = 16;
    samples = 101;
  }

  // ===============================
  //      Adding Blob operation     
  // ===============================

  // TODO:  This function will add the blob to a vector, it is the
  //        most complex operation of the entire process
  void addBlob(const Blob &currentBlob){
    bool added(false);
      
    for (ObjIter obj(objects.begin());
	 ((obj < objects.end()) && !added); obj++){
      if (!blobsDiff((*obj), currentBlob)){ // If the blob is similar
	// to the current object, update this object with the info
	added = true;
	if (obj->blobs.size() < g_max_blobs_in_object){
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
  bool inBounds(const int &x, const int &y){
    return (((y >= 0) && (x >= 0)) &&
	    ((y < img.rows) && (x < img.cols)));
  }

  // Pre:  img, x, y , xMove, yMove all defined, optional initial
  //       STARTING_JUMP_SCALE and maxChannelDiff.
  // Post: The farthest point in the (x,y) direction specified that
  //       does NOT differ by more than "maxChannelDiff" on any ONE of
  //       the channels in the pixel, so color matters. The edge of
  //       the image is returned if it is reached.
  Pt jumpToEdge(int x, int y,
		const int &xMove, const int &yMove,
		const Px &blobColor){
    int jumpScale = STARTING_JUMP_SCALE;
    while (jumpScale >= MIN_JUMP_SCALE){
      x += (xMove*jumpScale); 
      y += (yMove*jumpScale);
      if (!inBounds(x, y) ||
	  channelsDiff(blobColor, img.at<Px>(y, x))){
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
  void tetraMedianSearch(Blob &toUpdate){
    Pt edge1(toUpdate.lower);    Pt edge2(toUpdate.lower);
    int  xDir(0);       int yDir(1);
    for (int i(0); i<computations; i+=2){
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

  // TODO:  This function will search for the new center of
  //        "blobToTrack" and will update all of the blob's member
  //        data with the results of the search
  bool trackBlob(Blob &blobToTrack){
    const Pt previousCenter(BLOB_CENTER(blobToTrack));
    Blob newBlob(img.at<Px>(previousCenter.y, previousCenter.x), 
		 previousCenter, previousCenter);
    if (!channelsDiff(blobToTrack.color, newBlob.color)){
      tetraMedianSearch(newBlob);
      updatePointAverage(blobToTrack.lower, newBlob.lower);
      updatePointAverage(blobToTrack.upper, newBlob.upper);
      updateColorAverage(blobToTrack.color, newBlob.color);
      blobToTrack.velocity = (BLOB_CENTER(newBlob) - previousCenter);
      return true;
    }
    return false;
  }

  // =============================
  //      Sampling operations     
  // =============================

  // TODO:  This function cycles through all blobs in an object and
  // Pre:  "obj" must be defined
  // Post: Cycles through all blobs in "obj" performs a blob search
  //       from the previous center point, 
  //       uses the new values to update the object or erase blobs
  //       from it if need be
  void reSampleObject(const ObjIter &obj){
    const Blob prediction(obj->color, 
			  obj->lower+obj->velocity, 
			  obj->upper+obj->velocity);
    // ^^ Uses the velocity to predict the next location that will be recorded
    obj->lower = obj->upper = BLOB_CENTER((*obj)); // Reset bounds of object
    for (BlobIter b(obj->blobs.begin()); b < obj->blobs.end(); b++){
      const bool canTrack(trackBlob(*b)); // Try and track the blob
      if ((!canTrack)  || blobsDiff(prediction, *b)){
	obj->blobs.erase(b); // Erase the blob from the object
	trackedBlobs--; // Decrement the total number of tracked blobs
      }
      else // Otherwise the blobs coincided with the prediction
	obj->updateObject(*b); // Update the object with this information
    }    
  }

  // TODO:  This will cycle through all objects and combine ones that
  //        are similar
  void mergeObjects(){
    const int halfSize = objects.size() / 2;
    for (ObjIter obj1(objects.begin()); obj1<objects.end(); obj1++){
      for (ObjIter obj2(obj1+1); obj2<objects.end();obj2++){
	if (!blobsDiff((*obj1), (*obj2))){ // If the two objects do not differ
	  setMinPt(obj1->lower, obj2->lower); // Set the min of both objects
	  setMaxPt(obj1->upper, obj2->upper); // Set the max of both objects
	  setMax(obj1->lifespan, obj2->lifespan); // Take the larger lifespan
	  objects.erase(obj2); // Erase the now insignificant object
	}
      }
    }
  }

  // Pre:  numSamples > 0
  // Post: The samples are taken with an even distribution across the
  //       image
  void sampleImgUniform(const int &numSamples){
    const int pixels(img.rows*img.cols);
    const int step(pixels / numSamples);
    for (int pixel(0); pixel<(pixels); pixel+=step){
      const Pt currentPoint(pixel%img.cols, pixel/img.rows);
      Blob currentBlob(img.at<Px>(currentPoint.y, currentPoint.x),
		       currentPoint, currentPoint);
      tetraMedianSearch(currentBlob);
      if (!badBlobDimensions(currentBlob))
	addBlob(currentBlob);    
    }    
  }

  // ==============================================
  //      Primary blob detection function call     
  // ==============================================

  // TODO:  This will run the blob detection algorithm, all parameters
  //        must have been set before calling this method
  void detectBlobs(Img &inImg){
    for (ObjIter obj(objects.begin()); obj<objects.end(); obj++){	      
      obj->lifespan++; // Increment the current running lifespan of this object
      reSampleObject(obj);
      if (obj->blobs.empty())
	objects.erase(obj);
      // WARNING:  Erasing from the vector I'm cycling through
    }
    mergeObjects(); // Combine all objects that have
    //        inadvertantly landed on top of each other
    int regularSamples(samples - objects.size()); // Compute the
    //        number of remaining samples to be taken from the image
    if (regularSamples > 0)
      sampleImgUniform(regularSamples); // Uniformly sample the image
    //        with remaining processes
  }
  
  // =========================
  //      Drawing methods     
  // =========================

  // Pre:  "outImg" is defined and the same as the one that
  //       "detectBlobs" was executed on
  // Post: Bounding boxes and vector lines for velocity are drawn for
  //       every single blob that has been discovered in the image
  void drawBlobBounds(Img &outImg){
    for (ObjIter obj(objects.begin()); obj<objects.end(); obj++){
      for (BlobIter b(obj->blobs.begin()); b<(obj->blobs.end()); b++){
	rectangle(outImg, b->lower, b->upper, 
		  cv::Scalar(b->color[0],b->color[1],b->color[2]));
	cv::line(outImg, BLOB_CENTER((*b)), 
		 BLOB_CENTER((*b)) + b->velocity,
		 cv::Scalar(0,255,0), 2);
      }    
    }
  }

  // Pre:  "outImg" is defined, that is where the boxes are drawn
  // Post: A box is drawn marking the lower and upper bounds of every
  //       object, also a line is drawn at the center of the object
  //       marking its average vector velocity
  void drawObjectsBounds(Img &outImg){
    for (ObjIter obj(objects.begin()); obj<objects.end(); obj++){
      int velocityColor(255);
      setMin(velocityColor, obj->lifespan);	       
      if (velocityColor > 50){
	rectangle(outImg, obj->lower, obj->upper, 
		  cv::Scalar(obj->color[0], obj->color[1], obj->color[2]));
	cv::line(outImg, BLOB_CENTER((*obj)), 
		 BLOB_CENTER((*obj))+obj->velocity,
		 cv::Scalar(0,velocityColor,0), 2);
      }
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
    vid >> temp; cv::flip(temp, img, 1);
    Img blobImg(img.clone());
    if (argc >= 2)
      img = cv::imread(argv[1]);

    // Initialize windows and create trackbars for runtime adjustments
    cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
    cv::waitKey(50);
    cv::namedWindow(TRACKBAR_WINDOW, CV_WINDOW_NORMAL);
    cv::waitKey(50);
    cv::namedWindow(BLOBS_WINDOW, CV_WINDOW_NORMAL);

    cv::createTrackbar("Computations", TRACKBAR_WINDOW, 
		       &computations, 80);
    cv::createTrackbar("Samples", TRACKBAR_WINDOW, &samples, 
		       (img.rows*img.cols) / 512);
    cv::createTrackbar("Minimum blob dimension", TRACKBAR_WINDOW,
		       &g_min_blob_dimension, img.rows / 2);
    cv::createTrackbar("Point difference threshold", TRACKBAR_WINDOW,
		       &g_point_diff_thresh, (img.cols / 10));
    cv::createTrackbar("Color dynamic average buffer",
		       TRACKBAR_WINDOW, &g_color_dab, 20);
    cv::createTrackbar("Position dynamic average buffer",
		       TRACKBAR_WINDOW, &g_pos_dab, 20);
    cv::createTrackbar("Max blobs in Object", TRACKBAR_WINDOW, 
		       &g_max_blobs_in_object, 100);
    cv::createTrackbar("Clear objects (1=true)", TRACKBAR_WINDOW,
    		       &clearObjects, 1);

    // Main test runs until user presses escape key
    while (cv::waitKey(1) != ESC_KEY){
      // Capture image for processing
      if (argc < 2){
	vid >> temp; cv::flip(temp, img, 1);
      }
      else
      	img = cv::imread(argv[1]);

      // Reset the blob image to black
      blobImg.setTo(cv::Scalar(0,0,0));

      // If the sliders are in valid positions then run the program
      if ((g_pos_dab > 0) && (g_color_dab > 0)){
	detectBlobs(img); // Build vectors of blobs in class
	drawBlobBounds(img); // Draw low level blob boundaries on original
	drawObjectsBounds(blobImg); // Draw high level boxes separately
      }

      // Show both images to the user
      cv::imshow(ORIGINAL_IMAGE, img);
      cv::imshow(BLOBS_WINDOW, blobImg);

      // Clear the vector if requested to do so
      if (clearObjects)
	objects.clear();
    }
  }

};
