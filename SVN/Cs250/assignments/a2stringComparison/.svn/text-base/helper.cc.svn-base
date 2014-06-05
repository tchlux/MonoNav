#include <iostream>
#include <fstream>
#include "helper.h"
#include "String.h"
#include "FileReader.h"
#include "List.h"

using namespace std;


//Pre:  Two character arrays terminated with \0 and a place to store
//      the error for the final result
//Post: An integer that is the index start location of the best
//      matched sub string, a -1 if it isn't a substring
int getBestMatch(char * mainString, char * subString, int & error){
  List indexValues; //A list of valid start locations for finding sub
                    //strings
  List errorValues; //list of errors at each index value in the
                    //previous list
  int index; //initialize variable for holding the index of the
             //minimum of the error list
  int start = 0; //index of start in mainString
  while (mainString[start] != '\0'){
    getError(mainString, subString, start, indexValues, errorValues);
    start ++;
  }
  if (indexValues.length() > 0){ //if a valid substring has been found
    error = errorValues.min(index); //get the index of the min of the
    index = indexValues.index(index);
    //      errors and save the minimum error
  }
  else{
    index = -1; //if there are no substrings, set the return value to -1
  }
  return (index); //return the index of the best match
}

//Pre:  Two character arrays terminated with \0 and an integer
//      starting index >= to 0 to begin the comparison in mainString
//      Two Lists, one of valid indices, and one of their errors
//Post: The error for valid subString startIndices is saved along with
//      the start index, otherwise nothing happens
void getError(char * mainString, char * subString, int startIndex,
	      List & indices, List & errors){
  int error = 0; //error count starts at 0
  int subCurr = 0; //index in the subString
  int mainCurr = startIndex; // index in mainString
  bool valid = mainString[startIndex] == subString[0]; //assert that
  //      this is a valid starting index for comparison
  while ((mainString[mainCurr] != '\0')&(valid)
	 &(subString[subCurr] != '\0')){ //valid start, and
    //      string is not done being compared
    if (mainString[mainCurr] == subString[subCurr]){ //if the values
      //      are equal
      subCurr ++; //increment both subCurr
      mainCurr ++;// and mainCurr
    }
    else{
      error ++; //bad match, error goes up
      mainCurr ++; //move mainCurr forward
    }
  }
  if ((subString[subCurr] == '\0')&(valid)){ //if it was a valid start
    //      and a full match was found for subString
    indices.add(startIndex); //add to valid indices List
    errors.add(error); //add the error to error list
  }
}

//Pre:  A list of bestMatchIndices, that is the start index of the
//      best matching substring >= 0 and an associated list of errors a
//      2D char array that holds each of the lines of the file, and
//      the name of the output file is given along with the output
//      filename 
//Post: The best match is saved for each string, No match if -1
void writeStringStats(List & bestMatchIndices,
		      List & errorAtIndices,
		      char ** fileStrings,
		      char * oFileName){
  ofstream outFile (oFileName); // Define an output stream associated
  //      with the output file.  
  int length = bestMatchIndices.length(); //define length of number of
  //      outputs
  if (outFile != NULL){ //if outFile is valid
    for (int i=0; i<length; i++){ //for every substring
      if (bestMatchIndices.index(i) != -1){
	outFile << "The best match for \"" << fileStrings[i+1]
		<< "\" in \"" << fileStrings[0] << "\" is at position "
		<< bestMatchIndices.index(i) << " with error "
		<< errorAtIndices.index(i) << ".\n";
      }
      else{
	outFile << "\"" << fileStrings[i+1]
		<< "\" does not have a match in \"" 
		<< fileStrings[0] << "\".\n";
      }
    }
  }
}
