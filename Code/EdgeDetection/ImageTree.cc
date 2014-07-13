#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <vector>
#include <assert.h>

#define SEARCH_CELL_SIZE 9    // The number of 'neighbors' every
                              // ITNode has, this is the box used to
                              // search for interesting pixels

// Namespace: This namespace holds operations for an "image tree" it
// should only be included once because it has "compilable"
// information in it. All headers and function definitions are
// included in this file, I know it is unorthodox, but I've yet to
// think of a cleaner way to organize this type of code.
namespace it{
  class ITNode{
  public:
    int _depth; // Depth of this node
    int _col;   // Col number
    int _row;   // Row number
    int _count; // Current number of children
    ITNode *_neighbors[SEARCH_CELL_SIZE-1]; 
    // "-1" Since the center cell will be the parent ITNode

    ITNode();
    ~ITNode();
    ITNode(const int &depth, const int &row, const int &col);
    int getIndex(const int &childNumber, int fullSize);
    bool interesting(const cv::Vec3b &current, 
		     const cv::Vec3b &potential);
    bool interestingChild(const int &childNumber);
    void checkInterest(const int &maxDepth);
    void shadeImage(cv::Mat &edgeTree);    
    void fillBounds(cv::Mat &image);
  };

  cv::Mat *_image(NULL);
  int _interestingThreshold(80);
  ITNode _itn[20*20];

  // TODO:  This function will build the ImageTree, _image != NULL
  void ImageTree(const int &maxDepth){
    assert(_image);      // Assert the image exists    
    for (int i=0; i<20*20; i++){
      _itn[i]._row = (_image->rows / 20) * (i / 20);
      _itn[i]._col = (_image->cols / 20) * (i % 20);
      _itn[i].checkInterest(maxDepth); // Begins the recursive tree build
    }
    // _itn._row = _image->rows / 2;
    // _itn._col = _image->cols / 2;

  }

  // TODO:  This function will create the edge tree image and show it
  //        next to the original image.
  void showImageTree(){
    assert(_image);
    cv::Mat edgeTree(_image->clone()); // Copy the image
    for (int i=0; i<20*20; i++)
      _itn[i].shadeImage(edgeTree);
    cv::imshow("Original Image", *_image);
    cv::imshow("Edge Tree Image", edgeTree);
    cv::waitKey(0);
  }

  // TODO:  This function will fill a given rectangle in an image
  void fillRectangle(cv::Mat &image, int minX,int minY,
		     int maxX,int maxY, cv::Vec3b &color){
    for (int col(minX); col<maxX; col++){
      for (int row(minY); row<maxY; row++){
	image.at<cv::Vec3b>(row,col) = color;
      }
    }
  }

  // ==============================================
  //      Image Tree Node function definitions     
  // ==============================================

  ITNode::ITNode(){
    _depth = 0;
    _row = _col = 0;
    _count = 0;
  };

  ITNode::~ITNode(){
    for (int child(0); child<_count; child++){
      delete(_neighbors[child]);
    }
  };
    
  ITNode::ITNode(const int &depth, const int &row, const int &col){
    _depth = depth;
    _row = row;
    _col = col;
    _count = 0;
  };

  // TODO:  This function draws large shaded regions in the given
  //        image provided based on this nodes depth and then
  //        recursively calls all of it's children to do the same
  void ITNode::shadeImage(cv::Mat &edgeTree){
    fillBounds(edgeTree);
    for (int child(0); child<_count; child++)
      _neighbors[child]->shadeImage(edgeTree);
  };

  // TODO:  This function generates the bounds based off the center of
  //        this node and the depth
  void ITNode::fillBounds(cv::Mat &image){
    int cols = image.cols;
    cols >>= (_depth+1);
    int rows = image.rows;
    rows >>= (_depth+1);

    int minX,minY,maxX,maxY;    
    minY = _row - rows;
    minX = _col - cols;
    maxY = _row + rows;
    maxX = _col + cols;

    if (minY < 0)
      minY = 0;
    if (minX < 0)
      minX = 0;
    if (maxY > image.rows)
      maxY = image.rows;
    if (maxX > image.cols)
      maxX = image.cols;
    cv::Vec3b color(255 / (_depth+1),
		    255 / (_depth+1),
		    255 / (_depth+1));
    it::fillRectangle(image, minX, minY, maxX, maxY, color);
  }

  // TODO:  This function will check if any of the 8 children would be
  //        interesting to look at, if so it creates nodes for them
  //        and recursively calls them to check interest
  void ITNode::checkInterest(const int &maxDepth){
    if (_depth < maxDepth){
      for (int nbrs(0); nbrs<SEARCH_CELL_SIZE; nbrs++){
	// WARNING:  This loop ends up searching the "4th" pixel which
	//        is the parent pixel itself, this will never be an
	//        interest point, would be faster if that were skipped
	if (interestingChild(nbrs)){
	  int col( getIndex(nbrs, (it::_image->cols)/20 ) );
	  int row( getIndex(nbrs, (it::_image->rows)/20 ) );
	  _neighbors[_count] = new ITNode(_depth+1, row, col);
	  _neighbors[_count]->checkInterest(maxDepth);
	  _count++; // Increment the number of children
	}
      }
    }
  };

  // TODO:  This method returns true if a pixel was declared interesting
  bool ITNode::interestingChild(const int &childNumber){
    int y(getIndex(childNumber, it::_image->rows));
    int x(getIndex(childNumber, it::_image->cols));

    bool outOfBounds( ((y < 0) || (x < 0)) ||
		      ((y > it::_image->rows) ||
		       (x > it::_image->cols)) );
    if (outOfBounds)
      return false;

    cv::Vec3b child(_image->at<cv::Vec3b>(y,x));
    cv::Vec3b me(_image->at<cv::Vec3b>(_row,_col));
    bool isInteresting( interesting(me, child) || 
			interesting(child, me)    );
    return isInteresting;
  };

  // TODO:  This returns if the current compared with the potential
  //        is 'interesting' (declared by user)
  bool ITNode::interesting(const cv::Vec3b &current, 
			   const cv::Vec3b &potential){
    cv::Vec3b diff(current - potential);
    int sum(diff.val[0] + diff.val[1] + diff.val[2]);
    return ( sum > it::_interestingThreshold );
  };

  // TODO:  This function calculates the index in a binary search
  //        given the full dimension and the child number (assuming an
  //        8 point box around a center point)
  int ITNode::getIndex(const int &childNumber, int fullSize){
    fullSize >>= (_depth+1); // Divide the full size by two depth+1
    //        times for a binary search pattern over the image
    if ( (childNumber / 3) == 0 ) 
      return _row - fullSize;

    else if ( (childNumber / 3) == 1 ) 
      return _row;

    else 
      return _row + fullSize;
  }

}; // END namespace it
