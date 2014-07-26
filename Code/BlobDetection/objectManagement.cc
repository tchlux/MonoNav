class Object;
typedef std::vector<Object> ObjVec;
typedef ObjVec::iterator ObjIter;

class Object : public Blob{
public:
  int numBlobs;
  IntPt extremeLower; // Holds the lower bound of the group
  IntPt extremeUpper; // Holds the upper bound of the group
  IntPt oldCenter; // Holds the previous center point

  Object(const Blob &b) : Blob(b), numBlobs(0), 
			  extremeLower(0,0), 
			  extremeUpper(0,0){}

  // TODO:  This function will add the given blob to this object and
  //  update its center point bounds
  void addBlob(const Blob &b){
    IntPt center(BLOB_CENTER(b));
    setMin(lower.x, center.x);
    setMin(lower.y, center.y);
    setMax(upper.x, center.x);
    setMax(upper.y, center.y);

    setMin(extremeLower.x, b.lower.x);
    setMin(extremeLower.y, b.lower.y);
    setMax(extremeUpper.x, b.upper.x);
    setMax(extremeUpper.y, b.upper.y);

    numBlobs++; // Increment the count for the number of blobs
    updateColorAverage(color, b.color);    
  }

  // TODO:  This function prepares this object to be resampled
  void reset(){
    extremeLower = lower;
    extremeUpper = upper;
    lower = upper = oldCenter = BLOB_CENTER((*this));    
    numBlobs = 0;
  }
  
};

// TODO:  This function returns true if "lower" and "upper" overlap "point"
bool overlaps(const IntPt &lower, const IntPt &upper, const IntPt &point){
  return (((lower.x < point.x)  &&
	   (lower.y < point.y)) &&
	  ((upper.x > point.x)  &&
	   (upper.y > point.y)));
}

// TODO:  This function goes through blobs and makes sure that all of
//        them are represented
void addBlobs(BlobVec &blobs, ObjVec &groups){
  for (BlobIter b(blobs.begin()); b<blobs.end(); b++){
    bool exists(false);
    for (ObjIter o(groups.begin()); o<groups.end(); o++){
      if ( (overlaps(o->extremeLower, o->extremeUpper, BLOB_CENTER((*b))) || 
	    overlaps(b->lower, b->upper, BLOB_CENTER((*o)))) &&
	   channelsSimilar(b->color, o->color) ){
	exists = true;
	o->addBlob(*b);	
	break;
      }
    }
    if (!exists)
      groups.push_back(Object(*b));
  }  
}

// TODO:  This function removes blobs that are not sustained well
void removeBlobs(ObjVec &groups){
  for (ObjIter o(groups.begin()); o<groups.end(); o++){
    if (o->numBlobs == 0)
      groups.erase(o);
  }
}

// TODO:  This function performs tracking with a set of groups
void trackGroups(BlobVec &blobs, ObjVec &groups){
  addBlobs(blobs, groups);
  removeBlobs(groups);
  std::cerr << "groups.size(): " << groups.size() << std::endl;
}

// TODO:  This resets all the objects in "groups"
void resetGroups(ObjVec &groups){
  for (ObjIter o(groups.begin()); o<groups.end(); o++)
    o->reset();
}


// Pre:  "outImg" is defined and is of the same dimensions as the one
//       that "detectBlobs" was executed on
// Post: Bounding boxes and vector lines for velocity are drawn for
//       every single blob that has been discovered in the image
void drawGroups(cv::Mat &outImg, ObjVec &groups, const int minBlobs){
  for (ObjIter g(groups.begin()); g<(groups.end()); g++)
    if (g->numBlobs >= minBlobs){
      rectangle(outImg, g->extremeLower, g->extremeUpper, 
		cv::Scalar(g->color[0], g->color[1], g->color[2]));
      line(outImg, g->oldCenter, BLOB_CENTER((*g)),
	   cv::Scalar(80, 200, 0));
    }
}
