#include <iostream> // for standard output
#include <fstream> // For reading in the text file
#include "Graph.h" // Holds all the letters and the before/after stats
#include "Loop.h" // List type used in graph
#include "LoopNode.h" // Used in Loop
#include "Tuple.h" // Used to hold letter occurance values

#define CHAR_BUFFER_SIZE 3
using namespace std;

// Pre:  count is a defined graph type.  Buff is a character array of
//       length CHAR_BUFFER_SIZE
// Post: The before and after characters are added for the middle
void addCharacter(Graph<vertex> & count, char * buff){  
  
};


// Pre:  argc = 2 argv[1] = filename
// Post: The occurance of letters before and after letters is counted
int main(int argc, char * argv[]){
  int status = 0;
  if (argc != 2){
    cout << "ERROR: Usage:  $ ./letterFreq fileName.ext";
  }
  else{
    Graph<vertex> count;      // Storage for the letters/frequencies
    // vertex defined in Graph.h
    ifstream inFile(argv[1]); // the text file to read from
    char buffer[CHAR_BUFFER_SIZE]; // Holder for chars from file
    buffer[0] = inFile.get(); // previous character
    buffer[1] = inFile.get(); // current character
    buffer[2] = inFile.get(); // next character
    while (! inFile.eof()){
      addCharacter(count, buffer); // update occ data
      buffer[0] = buffer[1]; buffer[1] = buffer[2];// Cycle characters
      buffer[2] = inFile.get();	// Get the next new character
    }
    
  }
  return(status);
}
