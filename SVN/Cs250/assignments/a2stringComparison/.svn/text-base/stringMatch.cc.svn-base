#include <iostream>
#include "List.h"
#include "helper.h"
#include "FileReader.h"

#define minNewLines 3

using namespace std;


//Pre:  command line args for infile and outfile are given A main
//      string is the first entry in the infile, followed by any
//      number of sub strings to be found in the main string
//Post: The closest match locations for each sub string are saved into
//      the out file
int main(int argc, char * argv[]){
  int returnStatus = 0; //Normal execution
  char * inFile = argv[1]; //the name of the inFile
  char * outFile = argv[2]; //the name of the outFile
  FileReader file(inFile); //the file stored in a class
  int fileLength = file.lengthL() - 1; // get the number of new line
  //      characters in the file, subtract one given a proper file was
  //      supplied that conatains one extra new line char at bottom
  if (fileLength >= minNewLines){ //if there are enough lines in
                                  //the file
    List bestMatchIndices; //Initialize list for storing best matches
    List errorAtIndices; //Init list for storing error at the best
    //      matches
    char ** lines = file.splitBy('\n', fileLength); //create a two
    //      dimmesional array of characters, one 'string' for each
    //      line, (split by new lines) 
    //ASSERT: fileLength does not change
    int error; //init storage for the error at given best matches
    for (int i=1; i<fileLength; i++){ //start at the first line to compare
      bestMatchIndices.add(getBestMatch(lines[0], lines[i], error));
      errorAtIndices.add(error);
      // calculate the index of the best match and save it
    }
    writeStringStats(bestMatchIndices, errorAtIndices, lines, outFile);
    //write all the data to the output file
  }
  else{
    cout << "Improper usage, in file and out file where infile has 3+ lines\n\n";
    returnStatus = 1;
  }
  return(returnStatus);
}
