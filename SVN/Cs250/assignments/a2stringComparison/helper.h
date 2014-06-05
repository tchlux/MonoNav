#ifndef INCLUDED_HELPER
#define INCLUDED_HELPER

#include "List.h"

//Pre:  Two character arrays terminated with \0 and a place to store
//      the error for the final result
//Post: An integer that is the index start location of the best
//      matched sub string, a -1 if it isn't a substring
int getBestMatch(char * mainString, char * subString, int & error);

//Pre:  Two character arrays terminated with \0 and an integer
//      starting index >= to 0 to begin the comparison in mainString
//      Two Lists, one of valid indices, and one of their errors
//Post: The error for valid subString startIndices is saved along with
//      the start index, otherwise nothing happens
void getError(char * mainString, char * subString, int startIndex,
	      List & indices, List & errors);

//Pre:  A list of bestMatchIndices, that is the start index of the
//      best matching substring >= 0 and an associated list of errors a
//      2D char array that holds each of the lines of the file, and
//      the name of the output file is given along with the output
//      filename 
//Post: The best match is saved for each string, No match if -1
void writeStringStats(List & bestMatchIndices,
		      List & errorAtIndices,
		      char ** fileStrings,
		      char * filename);
#endif
