#include <iostream>
#include "Matrix.h"
#include "Tuple.h"
#include "LinkedList.h"
#include "Node.h"
#include "defs.h"

#define DEFAULT_ADJ false	// initial value in the adj matrix
#define DEFAULT_DIST 0 		// initial value in the dist matrix

#define DISTANCE_ACCURACY_INCREMENT .01 //the increment used to find
// the distance between two points.  Distance value is incremented by
// this and then squared repeatedly until it's value exceeds the sum
// of the squares of the x and y difference.


using namespace std;


template <class T>
class Graph{

private:
  //CI: Graph is a set of data that all lies in some common plane.
  //    if there are vertices, there is a delta vector

  LinkedList<T> vertices;      //List of all vertices in the graph
  LinkedList<int> deltaVector; //delta vector for graph
  Matrix<bool> adjacency;      //adjacency matrix for vertices 
  Matrix<int> distance;        //distance matrix for vertices
  int threshold;               //threshold for connectivity of nodes
  int maxColors;	       //Maximum colors needed to color graph

public:

  // ======================
  //      Constructors     
  // ======================

  //  Default consructor
  Graph(){
    threshold = 0;
    adjacency.setInit(DEFAULT_ADJ);
    distance.setInit(DEFAULT_DIST);
  };

  //  Given both the vertices, delta vector, and threshold
  Graph(LinkedList<T> & newVerts, LinkedList<int> & newDV,
	int thresh){
    threshold = thresh;
    vertices = newVerts;
    deltaVector = newDV;
    adjacency.setInit(DEFAULT_ADJ);
    distance.setInit(DEFAULT_DIST);
  }

  //  Copy constructor
  Graph(Graph & other){
    (*this) = other;
  };

  // Pre:  other is a well defined graph object
  // Post: This is made to be a copy of other
  Graph & operator=(Graph & other){
    vertices = other.vertices;
    deltaVector = other.deltaVector;
    adjacency = other.adjacency;
    distance = other.distance;
    threshold = other.threshold;
    return(*this);
  };

  // ========================================
  //      Graph initialization functions     
  // ========================================

  // Pre:  point is defined
  // Post: point is added to the list of vertices, all new cells in
  //       the matrices are set to initialized values
  void addVertex(vertex & point){
    vertices.addBack(point);
    adjacency.expand();//grow the adjacency and distance matrices
    distance.expand(); //by one to hold the new vertex
  };

  // Pre:  dv is defined, > 0
  // Post: this delta vector value is added to the list of dv's
  void addDeltaVector(int dv){
    deltaVector.addBack(dv);
  };

  // Pre:  t is defined
  // Post: The value of t is stored as threshold
  void setThreshold(int t){
    threshold = t;
  };

  // =============================================
  //      Generation functions (for coloring)     
  // =============================================

  // Pre:  vertices and adjacency are defined
  // Post: The distance matrix is produced
  void genDist(){
    int size = vertices.getSize(); // Size of the matrices
    Matrix<bool> current(adjacency); //current working matrix
    for (int round=0; round<size; round++){ //for i in range max(len)
      for (int row=0; row<size; row++){ //for row in adjacency
	for (int col=0; col<size; col++){ //for col in adjacency
	  if ((current[row][col])&&
	      (distance[row][col]==DEFAULT_DIST)){
	    //^^ if this slot is true and hasn't already been found
	    distance[row][col] = round+1;
	  } // End if(curr...
	} // End for(col=0...
      }	// End for(row=0...
      current *= adjacency; //multiply current by adjacency
    }
  };

  // Pre:  a and b are defined in vertices
  // Post: The euclydian distance between a and b
  float seperation(Node<vertex> * a, Node<vertex> * b){
    int null; //holder for unnecessary left data
    Tuple<int, int> first; //holder for a (x,y) data
    Tuple<int, int> second; //holder for b (x,y) data
    first = (a->getData().getLeft()); //store data from a in first
    second = (b->getData().getLeft()); //store data fro b in second
    int sum = (((first.getLeft()-second.getLeft())   * 
		(first.getLeft()-second.getLeft()))  +
	       ((first.getRight()-second.getRight()) * 
		(first.getRight()-second.getRight())));
    // ^^ (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
    float dist = 1.0;
    while (dist * dist < sum){
      dist += DISTANCE_ACCURACY_INCREMENT;
    }
    //^^ (sum) ** .5 ~approximately
    return (dist - DISTANCE_ACCURACY_INCREMENT);    
  };

  // Pre:  vetices and deltaVector are defined
  // Post: adjacency matrix is generated
  void genAdj(){
    //for vertex in vertices
    Node<vertex> * one;
    Node<vertex> * two;
    int size = vertices.getSize();
    for (int a=0; a<size; a++){
      one = vertices[a];
      //for other vertex in vertices
      for (int b=1; b<size; b++){
	two = one->traverseCyclic(b, vertices.getFront());
	if (seperation(one, two) < threshold){
	  adjacency[a][(a+b)%size] = true;
	}
      }
    }
  };

  // Pre:  distance and delta vector are defined
  // Post: boolean that represents whehter or not any node's colors
  //       are in conflict with other node's colors
  bool inConflict(){
    Node<vertex> * head = vertices.getFront(); //holder for front of v
    Node<vertex> * current; //current node being checked
    int numVs = vertices.getSize(); //number of vertices
    int dvSize = deltaVector.getSize(); //size of delta vector
    vertex data1; //holder for first vertex
    vertex data2; //holder for second vertex
    int difference; //holder for difference in color
    int dist; //holder for the current distance between nodes
    int currentDelta; //holder for current delta vector value
    bool conflict = false; //return value
    for (int row=0; ((row<(numVs-1))&&(!conflict)); row++){
      // ^^ (numVs-1) bc the last row will only hold a 0
      for (int col=row+1; ((col<numVs)&&(!conflict)); col++){
	// row+1 bc [row][row] will be on the diagonal aka 0
	data1 = (vertices[row])->getData();
	data2 = (vertices[col])->getData();
	if ((data1.getRight() != DEFAULT_COLOR) &&
	    (data2.getRight() != DEFAULT_COLOR)){
	  difference = data1.getRight() - data2.getRight();
	  //^^ the difference between the colors of the two nodes
	  dist = distance[row][col]; //get distance between two nodes
	  if ((dist-1) < deltaVector.getSize()){ //if that is in dv
	    // range, dist-1 since the dv is index accessed
	    currentDelta = (deltaVector[dist-1])->getData();
	    //^^ delta vector for the given two nodes at that dist
	    if ((difference < currentDelta) &&//if the abs(difference)
		(-difference < currentDelta)){//is less than delta
	      conflict = true; //that is a conflicting color combo
	    }//End if ((difference > ...
	  }//End if (dist < delta  ...
	}//End if ((data1.getRig ...
      }//End for (int col=row+ ...
    }//End for (int row=0; ((...
    return (conflict);
  }

  // Pre:  start, and max > 0, *curr defined
  // Post: Recursive check if with given max and start can the graph
  //       be colored
  bool backtrack(int max, Node<vertex> * curr, int depth){
    bool success = false; //boolean return value, successful addition
    if (depth < vertices.getSize()){ //if not done going through vList
      vertex data;
      for (int color=0; ((color<max)&&(!success)); color++){
	data = curr->getData(); //get the current data from curr
	data.setRight(color); //set it's color to be color
	curr->setData(data); //set that data back into curr
	if (!(inConflict())){ //if one of them works, recurse
	  success = backtrack(max, curr->getNext(), depth+1);
	}
	else{ //else, that color didn't work
	  data.setRight(DEFAULT_COLOR);//reset to default
	  curr->setData(data);//save back to node and continue
	}
      }
    }
    else{//made it through every single vertex
      success = true;  //it was a success
    }
    return(success);
  };

  // Pre:  maxColors and done are both defined
  // Post: boolean value for if this maxColors works
  bool canColor(int maxColors, bool & done){
    int size = vertices.getSize();
    Node<vertex> * curr = vertices.getFront();
    for(int start=0; ((start<maxColors)&&(!done)); start++){
      done = backtrack(maxColors, curr, 0);
    }
    return (done);
  };

  // Pre:  vertices is defined, deltaVector is defined
  // Post: adjacency, distance, colors of vertices are defined, the
  //       integer range of colors used is returned
  int color(){
    genAdj(); //generate a new adjacency matrix
    genDist(); //generate a new distance matrix
    maxColors = (deltaVector[0])->getData() * vertices.getSize();
    // ^^ maximum # colors = max(deltaVector) * (# vertices)
    int shift = maxColors; //The initial shift amount for maxColors
    bool done = false; //whether or not a coloring scheme was found
    while (!done){ //while a successful color has not been found
      shift = (shift+1)/2; //reduce the value of shift by half for bin
      // search, being sure to actually test shift of 1
      maxColors -= shift; //take shift from current maxColors
      canColor(maxColors, done); //try to color with the given shift
      if (done){ //if we could color with that shift
	if (shift > 0){ //if all shifts haven't been tested
	  done = false; //switch done to false and continue
	}//End if (shift >...
      }//End if (done){ ...
      else{ //Couldn't color with the previous maxColors
	maxColors += shift; //shift it back right some
	if (shift == 1){ //if shift=1 has been tested
	  shift = 0; //set shift to 0
	}//End if (shift >...
      }//End else{      ...
    }//End while (!don...
    return(maxColors-1); //ASSERT: this is the smallest number of 
  };


  // Pre:  out is defined
  // Post: The list of vertices is printed with proper format
  ostream & printVertices(ostream & out){
    Node<vertex> * curr = vertices.getFront();
    out << "Vertices: {";
    while (curr->getNext() != NULL){
      out << curr->getData().getLeft() << ", ";
      curr = curr->getNext();
    }
    out << curr->getData().getLeft() << "}" << endl;
    return(out);
  }

  // ============================
  //      Print data methods     
  // ============================

  // Pre:  out is defined
  // Post: the edges are listed
  ostream & printEdges(ostream & out){
    out << "Edges = {";
    Tuple<int,int> temp; //holder for current x,y pair
    for (int row=0; row<(vertices.getSize()); row++){
      for (int col=(row+1); col<vertices.getSize(); col++){
	if (adjacency[row][col] == true){
	  temp = vertices[row]->getData().getLeft(); //get the x,y
	  out << temp << " - ";
	  temp = vertices[col]->getData().getLeft(); //get the x,y
	  out << temp << ", ";
	}
      }
    }
    out << "\b\b}" << endl; //get rid of the last comma and close
    return(out);
  }

  // Pre:  out is defined
  // Post: contents of out modified with delta vector information
  ostream & printDelta(ostream & out){
    out << "delta = (";
    Node<int> * curr = deltaVector.getFront();
    while (curr->getNext() != NULL){
      out << curr->getData() << ", ";
      curr = curr->getNext();
    }
    out << curr->getData() << "))" << endl;
    return(out);
  }

  // Pre:  out is defined
  // Post: contents of out modified with color information
  ostream & printColors(ostream & out){
    Node<vertex> * curr = vertices.getFront();
    while (curr!= NULL){
      out << curr->getData().getLeft() << " coloured ";
      out << curr->getData().getRight() << endl;
      curr = curr->getNext();
    }
    out << "Colouring span = " << maxColors-1 << "." << endl;
  }

  // ===========================
  //      Ostream operator     
  // ===========================

  friend ostream & operator<<(ostream & out, Graph & g){
    out << "Graph: (with threshold distance " 
	<< g.threshold << ")" << endl;

    g.printVertices(out);

    g.printEdges(out);

    out << "L(k) colouring: (with k = " << g.threshold << " and ";
    g.printDelta(out);

    g.printColors(out);
    return(out);
  };
};
