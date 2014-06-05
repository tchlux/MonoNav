#include <iostream>
#include <fstream>
#include "FileReader.h"
#include "List.h"
#include "String.h"

using namespace std;

//Default Constructor
//Pre:  
//Post: theFile is initialized in memory
FileReader::FileReader(){
  hasFile = false;
}

//Pre:  An array of characters that is the filename is given
//Post: theFile is initialized in memory and filled
FileReader::FileReader(char * fileName){
  hasFile = false;
  readFile(fileName);
}

//Pre:  The file is given as a String class
//Post: theFile is initialized in memory and filled
FileReader::FileReader(String fileName){
  hasFile = false;
  char * newFileName = fileName.retExactArray();
  readFile(newFileName);
}

///PRIVATE METHODS///

//Pre:  Integer index for starting the search,
//      and the character to search for in theFile
//Post: The number of characters from [start, char)
int FileReader::countToNextChar(int start, char ch) const{
  int curr = start; //temp place holder
  char chr = theFile.index(curr); //current character
  while ((chr != ch)&(chr != '\0')){ //current != search
    curr ++; //increment place holder
    chr = theFile.index(curr); //get new character
  }
  return (curr - start); //+1 to be inclusive on start
}

//Pre:  
//Post: Deletes the currently stored String, and re initializes it
void FileReader::deleteFile(){
  theFile.reset(); //call reset on the file
  hasFile = false; //no file imported
}

//Pre: The filename is given as a character array
//Post: theFile is filled with the characters from the file
void FileReader::readFile(char * fileName){
  if (hasFile){
    cout << "File has already been imported!\n To re-import, call deleteFile first and then import."
	 << endl;
  }
  else{
    ifstream inFile(fileName); //get the file
    if (inFile == NULL){ //if it exists
      cout << "Input file did not exist! Read aborted!"
	   << endl;
    }//end if inFile exists
    else{
      char chr; //storage for current character
      inFile.get(chr); //get new character
      while (!inFile.eof()){ //while not at end of file
	theFile.add(chr); //add char to file
	inFile.get(chr); //get new character
      }
      hasFile = true; //file imported
      inFile.close(); //close the file
    }//end NULL file else
  }//end hasFile else
}

///PUBLIC METHODS///

//Pre:  
//Post: The length of the file in characters is returned
int FileReader::lengthC() const{
  return (theFile.length());
}

//Pre:  
//Post: The length of the file in lines is returned
int FileReader::lengthL() const{
  return (theFile.count('\n'));
}

//Pre:  The array of characters to be filled of length stop-start + 1
//      start & stop are indices in theFile 
//Post: The given array is filled with values from start to stop
void FileReader::fillArray(char * array, int start, int stop) const{
  for (int i=start ; i < stop; i++){
    array[i-start] = theFile.index(i); //shift all values over to
				       //appropriate indices and
				       //transfer them to the given
				       //array of characters
  }
  array[stop-start] = '\0'; //add terminator
}

//Pre:  A character to divide the file by is given, and a reference
//      to an integer that holds the size of the array
//Post: An array of character arrays
char ** FileReader::splitBy(char ch, int & length) const{
  length = theFile.count(ch); //save length to the given reference,
  //      length is the number of array references that will be
  //      present
  int curr = 0; //place holder in stringArray
  char ** stringArray = new char*[length]; //get heap space mem for array
  int size; //variable for holding the size of the current string
  for (int i=0; i < theFile.length(); i++){
    size = countToNextChar(i, ch);
    stringArray[curr] = new char[size+1];
    fillArray(stringArray[curr], i, size+i); //fill the array
    i = i+size; //increment i, +1 to not include the split character
    curr ++;
  }
  //Assert:   The whole file has been added
  //          The characters that were split by are removed
  //          The character arrays each hold a sub string
  //          Length has been set to the number of strings
  return (stringArray);
}

// Pre:  
// Post: The file is printed from the string class
void FileReader::print() const{
  theFile.print();
}

