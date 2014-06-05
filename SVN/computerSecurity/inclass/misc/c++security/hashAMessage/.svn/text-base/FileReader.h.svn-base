#ifndef INCLUDED_FileReader
#define INCLUDED_FileReader

#include "String.h"


class FileReader{

 private:

  String theFile; //the file stored as a string
  bool hasFile; //currently contains a file

  //CI: thefile is a pointer to a String class that has all standard
  //    attributes and memory allocations


  //Pre:  Integer index for starting the search,
  //      and the character to search for
  //Post: The number of characters from [start, char)
  int countToNextChar(int start,  char ch) const;

  //Pre:  
  //Post: Deletes the currently stored String, and re initializes it
  void deleteFile();

 public:

  //Default Constructor
  //Pre:  
  //Post: theFile is initialized in memory
  FileReader();

  //Pre:  An array of characters that is the filename is given
  //Post: theFile is initialized in memory and filled
  FileReader(char * fileName);

  //Pre:  The file is given as a String class
  //Post: theFile is initialized in memory and filled
  FileReader(String fileName);

  //Pre: The filename is given as a character array
  //Post: theFile is filled with the characters from the file
  void readFile(char * fileName);

  //Pre:  
  //Post: The length of the file in characters is returned
  int lengthC() const;

  //Pre:  
  //Post: The length of the file in lines is returned
  int lengthL() const;

  //Pre:  The array of characters to be filled, start & stop are
  //      indices in theFile
  //Post: The given array is filled with values from start to stop
  void fillArray(char * array, int start, int stop) const;

  //Pre:  A character to divide the file by is given, and a reference
  //      to an integer that holds the size of the array
  //Post: An array of character arrays
  char ** splitBy(char ch, int & length) const;

  // Pre:  
  // Post: The file is printed from the string class
  void print() const;


};

#endif
