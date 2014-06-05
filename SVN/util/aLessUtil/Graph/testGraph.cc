#include "Graph.h"
#include <iostream>

using namespace std;

// Used for testing the Graph class
int main(int argc, char * argv[]){
  int status = 0; 		// Return status
  Graph<vertex> test; 		// default constructor (using vertex
				// class defined in Graph.h)
  cout << "Graph default constructor ran" << endl;

  ciTup data0('a', 1);		// data to be held in first vertex
  ciTup data1('c', 1);		// data to be held in first vertex
  vertex testv0;
  testv0.left() = 'b';
  testv0.right().left().add(data0); // add a w/ occurance 1 before
  testv0.right().right().add(data1); // add c w/ occurance 1 after
  test.addVertex(testv0);	     // add this vertex to the graph
  cout << "Vertex added" << endl;

  cout << "Graph with one vertex" << endl;
  cout << test << endl;

  return(status);
}
