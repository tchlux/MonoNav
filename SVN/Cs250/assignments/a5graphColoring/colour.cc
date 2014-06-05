#include <iostream>
#include <fstream>

#include "defs.h"
#include "Tuple.h"
#include "LinkedList.h"
#include "Graph.h"

#define USAGE_ERROR "Usage Erorr: ./colour points.txt delta.txt"
#define NUM_ARGS 3 //number of args for proper run
#define MAX_LINE_SIZE 10 //maximum size of input line
#define NUMS_PER_LINE 2 //numbers on one line in points.txt file
#define ORD_ZERO (int) '0' //used for changing chars to digits
#define DECIMAL 10 //used for shifting the digits in a decimal number

using namespace std;

// Pre:  line is defined char* of max length 10 and terminated
// Post: the two numbers from the line are stored in a tuple
Tuple<int,int> getXY(char * line){
  Tuple<int,int> xyTup(0,0); //storage for the returnValue
  int digit = 0; //holder for the current numerical digit
  int i = 0; //iterator variable w/ larger scope
  while (line[i] != ' '){
    digit *= DECIMAL;
    digit += ((int) line[i]) - ORD_ZERO;
    xyTup.setLeft(digit);
    i++;
  }
  i++; //increment past ' '
  digit = 0; //reset digit
  while (line[i] != '\0'){
    digit *= DECIMAL;
    digit = ((int) line[i]) - ORD_ZERO;
    xyTup.setRight(digit);
    i++;
  }
  return (xyTup); //return the final Tuple
}

// Pre:  points is defined ifstream, graph is defined
// Post: All of the vertices in points are added to graph
void getVertices(ifstream & points, Graph<vertex> & g){
  Tuple<int,int> xyPos; //holder for x,y position of vertex
  vertex current(xyPos, DEFAULT_COLOR); //holder for current vertex
  char line[MAX_LINE_SIZE]; //storage for current line
  points.getline(line, MAX_LINE_SIZE); //get line
  while (! points.eof()){
    xyPos = getXY(line); //get the next x,y pair
    current.setLeft(xyPos); //set it as the location of current
    g.addVertex(current); //add this vertex to the graph
    points.getline(line, MAX_LINE_SIZE); //get line
  }
  //Assert all x,y pairs from ponits have been added to graph
  points.close();
}

// Pre:  delta is defined ifstream, graph is defined
// Post: All of the delta vector values are added to graph
void getDeltaVector(ifstream & delta, Graph<vertex> & g){
  char c = delta.get(); //current character in delta
  int d = 0; //current delta vector | threshold value
  while (c != '\n'){
    d = (d * DECIMAL) + ((int) c) - ORD_ZERO;
    c = delta.get(); //get the next character
  }
  g.setThreshold(d); //set the given int to be the threshold
  // ASSERT: on the second line of delta file
  c = delta.get(); //get the first number on the next line
  while (c != '0'){
    d = 0; //reset the delta vector to 0
    while (c != ' '){
      d = (d * DECIMAL) + ((int) c) - ORD_ZERO;
      c = delta.get();
    } //End for(; lin...
    g.addDeltaVector(d);
    c = delta.get(); //get the next character after the ' '
  } //End for(int i...
  // ASSERT: all delta vectors have been retrieved from delta
  delta.close();
}

// Pre:  argc = 3, argv = ["colour", "points file", "delta file"]
// Post: A graph is produced and colored
int main(int argc, char * argv[]){
  int status = 0;
  if (argc != NUM_ARGS){
    cout << USAGE_ERROR << endl;
  }
  else{
    ifstream points(argv[1]); //get the points file
    ifstream delta(argv[2]);  //get the delta file
    Graph<vertex> g;    //storage for graph    
    getVertices(points, g); //get all vertices for graph from file
    getDeltaVector(delta, g); //get delta vector from file
    g.color(); //color the graph appropriately
    cout << g; //print the graph information
  }
  return(status);
}
