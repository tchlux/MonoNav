#include <iostream>
#include "Tuple.h"
#include "Loop.h"
#include "LoopNode.h"
#include "Matrix.h"

// This compiler for this must have access to the above files

#define DEFAULT_ADJ false 	// default value in adjacency matrix
#define DEFAULT_DIST -1		// default value in distance matrix

using namespace std;

typedef Tuple<char, int> ciTup; //char int Tuple
typedef Loop<ciTup> ciLoop; //char int Tuple LinkedList
typedef Tuple<ciLoop, ciLoop> beAft; //holds a linked list of
 //(char, int)s for before and after self
typedef Tuple<char, beAft> vertex; // Often used as data type T

template <class T>
class Graph{

private:
  //CI: Graph is a set of data that all lies in some common plane.
  //    if there are vertices, there is a delta vector

  Loop<T> vertices;            //List of all vertices in the graph
  Matrix<bool> adjacency;      //adjacency matrix for vertices 
  Matrix<int> distance;        //distance matrix for vertices

public:

  // ======================
  //      Constructors     
  // ======================

  //  Default consructor
  Graph(){
    adjacency.setInit(DEFAULT_ADJ);
    distance.setInit(DEFAULT_DIST);
  };

  //  Copy constructor
  Graph(Graph<T> & other){
    adjacency.setInit(DEFAULT_ADJ);
    distance.setInit(DEFAULT_DIST);
    (*this) = other;
  };

  // Pre:  other is a well defined graph object
  // Post: This is made to be a copy of other
  Graph & operator=(Graph<T> & other){
    vertices = other.vertices;
    adjacency = other.adjacency;
    distance = other.distance;
    return(*this);
  };

  // ============================
  //      Accessor functions     
  // ============================

  // Pre:  other is defined properly (primarily only left)
  // Post: 
  bool has(T & other){
    LoopNode<T> * temp = LoopNode<T>(other);
    return(vertices.has(temp));
  }

  // ========================================
  //      Graph initialization functions     
  // ========================================

  // Pre:  point is defined
  // Post: point is added to the list of vertices, all new cells in
  //       the matrices are set to initialized values
  void addVertex(T & point){
    vertices.add(point);
    adjacency.expand();//grow the adjacency and distance matrices
    distance.expand(); //by one to hold the new vertex
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
	    //^^ if this slot is true in current and not in distance
	    distance[row][col] = round+1;
	  } // End if(curr...
	} // End for(col=0...
      }	// End for(row=0...
      current *= adjacency; //multiply current by adjacency
    }
  };

  // Pre:  a and b are defined in vertices
  // Post: bool, if they are adjacent
  bool adjacent(LoopNode<T> * a, LoopNode<T> * b){
    return(false);		// Currently not implemented
  };

  // Pre:  vetices and deltaVector are defined
  // Post: adjacency matrix is generated
  void genAdj(){
    LoopNode<T> * one;	// Holder for first node of comparison
    LoopNode<T> * two;	// Holder for the second
    int size = vertices.getSize(); // Size of the Loop
    for (int a=0; a<size; a++){	//for vertex in vertices
      one = vertices[a];
      for (int b=1; b<size; b++){ //for other vertex in vertices
	two = one->traverse(b);
	if (adjacent(one, two)){
	  adjacency[a][(a+b)%size] = true;
	}
      }
    }
  };


  // ===========================
  //      Ostream operator     
  // ===========================

  friend ostream & operator<<(ostream & out, Graph<T> & g){
    out << "Graph: " << endl;
    out << "  Vertices: " << endl << g.vertices << endl;
    out << "  Adjacency: " << endl << g.adjacency << endl;
    out << "  Distance: " << endl << g.distance << endl;
    return(out);
  };
};
