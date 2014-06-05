#include "string"
#include "sstream"
#include "List.h"

#define CHAR_NOT_FOUND -1
#define REPLACEMENT_LEN 1
#define REPEATED_TIMES 1
#define FORWARDSLASH '/'
#define SPACE ' '

using namespace std;

// =============================================
//      Functions for parsing certain files     
// =============================================
namespace Parse{

  // Pre:  str defined, search and replace defined
  // Post: All occurances of 'search' are replaced by 'replace'
  void replaceChar(string & str, char search, char replace){
    int pos = 0;
    while ( pos != CHAR_NOT_FOUND ){
      pos = str.find_first_of(search, pos);
      if (pos != CHAR_NOT_FOUND){
	str.replace(pos, REPLACEMENT_LEN, REPEATED_TIMES, replace);
      }
    }
  }
  
  // Pre:  line a sequence of floats separated by spaces
  // Post: A new list that contains the floats from the line is
  //       appended to the given list
  void extractFloats(std::stringstream & line, List<float> & list){
    float value;
    while (! line.eof()){
      line >> value; // Extract a float
      list.append(value); // add that value to the vector
    }
  }
		     
  // Pre:  line a sequence of ints separated by spaces
  // Post: A new list that contains the ints from the line is
  //       appended to the given list
  void extractInts(std::stringstream & line, List<int> & list){
    int value;
    while (! line.eof()){
      line >> value; // Extract a int
      list.append(value); // add that value to the vector
    }
  }

  // Pre:  line is a face line from an obj file
  // Post: The vertex, texture, and normal is extracted for this line
  void faceLine(std::stringstream & line, List<int> & face){
    string vtn; // Holder for set of vertex/texture/normal
    while (! line.eof()){
      vtn.clear(); // Clear any data that might be in vtn
      line >> vtn; // Extract data set from line
      replaceChar(vtn, FORWARDSLASH, SPACE); // Replace all slashes
      // with spaces on this vertex/texture/normal
      stringstream vtnStream(vtn); // Send this to a stream object
      extractInts(vtnStream, face); // Add integers to faceData
    }
  }

};
