#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector>
#include <assert.h>

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"
#define TRACKBAR_WINDOW "Adjustable parameters"
#define ESC_KEY 1048603 // 27 Escape key on hp-elitebook
#define CHANNEL_DIFF_THRESH 25 // 10% channel difference
#define STARTING_JUMP_SCALE 16 // Start distance for jumping to edge
                               //  of blobs
#define MIN_JUMP_SCALE 1 // The lowest jump allowed

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

// Pre:  "px1", "px2", CHANNEL_DIFF_THRESH defined, pixels have three
//        channels
// Post: true if the SQUARED difference in pixel values for any ONE
//       channel exceed "maxChannelDiff"
bool channelsDiff(const Px &px1, const Px &px2){
  if (((px1[0]-px2[0]) > CHANNEL_DIFF_THRESH) || 
      ((px2[0]-px1[0]) > CHANNEL_DIFF_THRESH) ||
      ((px1[1]-px2[1]) > CHANNEL_DIFF_THRESH) || 
      ((px2[1]-px1[1]) > CHANNEL_DIFF_THRESH) ||
      ((px1[2]-px2[2]) > CHANNEL_DIFF_THRESH) || 
      ((px2[2]-px1[2]) > CHANNEL_DIFF_THRESH))
    return true;
  return false;
}

// Pre:  "toUpdate" and "newPoint" are both defined fully
// Post: "toUpdate" is modified to be more similar to "newPoint", the
//       amount it is adjusted is deterimed by a combination of the
//       magnitude of the difference between "toUpdate" and "newPoint"
//       and the denominator (average contribution factor) of the
//       operation (see dynamic average explanation at top of file)
void updatePointAverage(Pt &toUpdate, Pt &newPoint){
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
  if ((yDir == -1) && (xDir == 0)){
    yDir = 1;
  }  else if ((yDir == 1) && (xDir == 0)){
    yDir = 0;
    xDir = 1;
  }  else if ((yDir == 0) && (xDir == 1)){
    xDir = -1;
  }  else if ((yDir == 0) && (xDir == -1)){
    yDir = -1;
    xDir = 1;
  }  else if ((yDir == -1) && (xDir == 1)){
    yDir = 1;
    xDir = -1;
  }  else if ((yDir == 1) && (xDir == -1)){    
    xDir = 1;
  }  else if ((yDir == 1) && (xDir == 1)){
    yDir = -1;
    xDir = -1;
  }  else if ((yDir == -1) && (xDir == -1)){
    yDir = -1;
    xDir = 0;
  }
}

// ====================
//      Blob Class     
// ====================

// TODO:  This class will hold the information for a blob
class Blob{
public:
  Px color;
  Pt lower;
  Pt upper;
  Pt velocity; // The blob's x and y velocity

  // Method:  Constructor given appropriate member data
  Blob(const Px &Color, const Pt &Lower, const Pt &Upper){
    color = Color;
    lower = Lower;
    upper = Upper;
    velocity = Pt(0,0);
  }

  // TODO: This method will update the current blob color so that it is
  //       ready to be resampled
  // Pre:  This blob is already defined from "img" and "img" has not
  //       changed dimensions
  // Post: The color average is updated for this blob
  Blob& prepareForResample(const Img &img){
    return(*this);
  }
};

// =============================================
//      Runtime Functions that require Blob     
// =============================================

// Pre:  box and currentBlob fully defined
// Post: true if "currentBlob" lies entirely inside of "box"
bool overlaps(const Blob &box, const Blob &currentBlob){
  const Pt center(BLOB_CENTER(currentBlob));
  return (((center.x > box.lower.x) &&
	   (center.y > box.lower.y)) &&
	  ((center.x < box.upper.x) &&
	   (center.y < box.upper.y)));
}

// TODO:  This function checks to see if "newPt" is a relative min or
//        maximum that should be stored in the current blob
void adjustMinMax(Blob &currentBlob, const Pt &newPt){
  setMinPt(currentBlob.lower, newPt);
  setMaxPt(currentBlob.upper, newPt);
}

// TODO:  Returns true if the blob doesn't meet requirements
bool badBlob(const Blob &b){
  return ((BLOB_WIDTH(b) < g_min_blob_dimension) ||
	  (BLOB_HEIGHT(b) < g_min_blob_dimension));    
}

// TODO:  This function returns true if the given blob is similar to
//        this object
bool blobSimilar(const Blob &blob1, const Blob &blob2){
  return (! (channelsDiff(blob1.color, blob2.color) ||
	     pointsDiff(blob1.lower, blob2.lower) || 
	     pointsDiff(blob1.upper, blob2.upper)) );
}

// ======================
//      Object Class     
// ======================

class Object : public Blob{
public:
  std::vector<Blob*> blobs;

  Object(Blob &blob):Blob(blob.color, blob.lower, blob.upper){
    blobs.push_back(&blob);
  }

  // TODO:  This method will add a blob to this object and adjust the
  //        bounds and color of this object
  void updateObject(Blob &blob){
    updatePointAverage(velocity, blob.velocity);
    updateColorAverage(color, blob.color);
    setMinPt(lower, blob.lower);
    setMaxPt(upper, blob.upper);
    blobs.push_back(&blob);
  }

  // TODO:  This method will return true if the given blob was made
  //        part of this object and false if it was not
  bool blobAdd(Blob &blob){
    if (blobSimilar((*this), blob)){
      updateObject(blob);
      return true;
    }
    return false;
  }
};


// ===========================
//      Tetramedian class     
// ===========================

// TODO:  This is the class for blob detection
class TetraMedian{
public:
  int computations;
  int samples;

  Img img;
  BlobVec blobs;
  ObjVec objects;

  TetraMedian(){
    computations = 16;
    samples = 101;
  }

  // =============================
  //      TetraMedian methods     
  // =============================

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

  // TODO:  This function will add the blob to a vector, it is the
  //        most complex operation of the entire process
  void addBlob(Blob &currentBlob){
    if (!badBlob(currentBlob)){
      bool newBlob(true);

      for (int b(0); b<blobs.size(); b++){      
	if (badBlob(blobs[b]))
	  blobs.erase(blobs.begin() + b);
      	else
	  if (overlaps(blobs[b], currentBlob))
	    newBlob = false;
      }    

      if ((newBlob) &&
	  (blobs.size() < samples))
	blobs.push_back(currentBlob);
    }
  }

  // Pre:  col and row are within the bounds of "img"
  // Post: Four different sloped lines are projected outwards starting
  //        from "oldBlob.center" in "img" and the median point of the
  //        "jumpToEdge" searches for both directions on that line is
  //        used as the starting point for the searches on the next
  //        line.  This is done with "computations" calls to the
  //        "jumpToEdge" function and updates the bounds
  void biDirection8(Blob &oldBlob){
    const Pt oldCenter(BLOB_CENTER(oldBlob));
    Pt edge1(oldCenter);    Pt edge2(oldCenter);
    Blob currentBlob(img.at<Px>(oldCenter.y, oldCenter.x), oldCenter, oldCenter);
    int  xDir(0);       int yDir(-1);
    for (int i(0); i<computations; i+=2){
      const int x((edge1.x+edge2.x)/2);
      const int y((edge1.y+edge2.y)/2);
      edge1 = jumpToEdge(x, y, xDir, yDir, currentBlob.color);
      setBiDirection8(xDir, yDir);
      edge2 = jumpToEdge(x, y, xDir, yDir, currentBlob.color);
      setBiDirection8(xDir, yDir);
      // Update min and max
      adjustMinMax(currentBlob, edge1);
      adjustMinMax(currentBlob, edge2);
    }  
    updatePointAverage(oldBlob.lower, currentBlob.lower);
    updatePointAverage(oldBlob.upper, currentBlob.upper);
    updateColorAverage(oldBlob.color, currentBlob.color);
    oldBlob.velocity = BLOB_CENTER(oldBlob) - oldCenter;
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
      biDirection8(currentBlob);
      addBlob(currentBlob);    
    }    
  }

  // TODO:  This will run the blob detection algorithm, all parameters
  //        must have been set before calling this method
  void detectBlobs(Img &inImg, BlobVec &inOut){
    int regularSamples(samples);

    if (blobs.size() > 0){
      for (int b(0); b < blobs.size(); b++)
	biDirection8(blobs[b].prepareForResample(img));
      regularSamples -= blobs.size();
    }

    if (regularSamples > 0)
      sampleImgUniform(regularSamples);

  }

  // TODO:  This method will cycle through all blobs and make
  //        "objects" out of similar blobs
  void buildObjectsVector(){
    std::vector<Pt> centers;
    for (int b(0); b<blobs.size(); b++){
      bool doneWithThisBlob(false);
      const Pt currentCenter(BLOB_CENTER(blobs[b]));
      for (int c(0); (c<centers.size() && !doneWithThisBlob); c++){
	if (currentCenter == centers[c]){
	  blobs.erase(blobs.begin()+b);
	  doneWithThisBlob = true;
	}
      }

      for (int obj(0); (obj<objects.size() && !doneWithThisBlob); obj++){
	doneWithThisBlob = objects[obj].blobAdd(blobs[b]);
      }
      if (!doneWithThisBlob)
	objects.push_back(Object(blobs[b]));
    }
  }
  
  // =========================
  //      Drawing methods     
  // =========================

  // Pre:  outImg is of the same dimensions as the image used to
  //         calculate all of the points stored in "blobs"
  // Post: outImg is marked with blue rectangles marking the bounds of
  //         the blobs stored in "blobs"
  void drawBlobBounds(Img &outImg){
    for (int b(0); b<blobs.size(); b++){
      rectangle(outImg, blobs[b].lower, blobs[b].upper, 
		cv::Scalar(blobs[b].color[0],
			   blobs[b].color[1],
			   blobs[b].color[2]));
      cv::line(outImg, BLOB_CENTER(blobs[b]), 
	       BLOB_CENTER(blobs[b])+blobs[b].velocity,
	       cv::Scalar(0,255,0), 2);
    }
  }

  // TODO:  This function will find blobs that are similar and build
  //        rectangles around them, to help clarify the image.
  void drawObjectsBounds(Img &outImg){
    for (int obj(0); obj<objects.size(); obj++){
      Pt upperRight(objects[obj].upper.x, objects[obj].lower.y);
      Pt lowerLeft(objects[obj].lower.x, objects[obj].upper.y);
      Pt bounds[4] = {objects[obj].lower, upperRight, 
		      objects[obj].upper, lowerLeft};
      rectangle(outImg, objects[obj].lower, objects[obj].upper, 
      		cv::Scalar(objects[obj].color[0],
      			   objects[obj].color[1],
      			   objects[obj].color[2]));
      cv::line(outImg, BLOB_CENTER(objects[obj]), 
	       BLOB_CENTER(objects[obj])+objects[obj].velocity*3,
	       cv::Scalar(0,255,0), 2);
    }    
  }

  // ====================================
  //      Testing and debugging code     
  // ====================================

  // TODO:  This method is for testing the blob detector
  void test(int argc, char *argv[]){
    Img temp;
    int clearBlobs(0);
    int clearObjects(1);
    cv::VideoCapture vid(argv[1]);
    vid >> temp;
    cv::flip(temp, img, 1);
    Img blobImg(img.clone());
    // if (argc >= 2)
    //   img = cv::imread(argv[1]);

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
    cv::createTrackbar("Clear blobs (1=true)", TRACKBAR_WINDOW,
		       &clearBlobs, 1);
    // cv::createTrackbar("Clear objects (1=true)", TRACKBAR_WINDOW,
    // 		       &clearObjects, 1);

    while (cv::waitKey(1) != ESC_KEY){
      // if (argc < 2){
	vid >> temp;
	if (temp.rows == 0){
	  vid.open(argv[1]);
	  vid >> temp;
	}
	cv::flip(temp, img, 1);
      // }
      // else
      	// img = cv::imread(argv[1]);


      blobImg.setTo(cv::Scalar(0,0,0));

      if ((g_pos_dab > 0) && (g_color_dab > 0)){
	detectBlobs(img, blobs);
	if (blobs.size() > samples)
	  blobs.erase(blobs.end()-(blobs.size()-samples), blobs.end());      
	buildObjectsVector();
	drawObjectsBounds(blobImg);
	drawBlobBounds(img);
      }

      cv::imshow(ORIGINAL_IMAGE, img);
      cv::imshow(BLOBS_WINDOW, blobImg);

      if (clearBlobs)
	blobs.clear();
      if (clearObjects)
	objects.clear();
    }
  }

};
