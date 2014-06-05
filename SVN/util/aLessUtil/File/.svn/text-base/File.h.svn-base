#ifndef INCLUDED_File
#define INCLUDED_File

#include "String.h"


class File{

 private:

  String * filename; //the name of the file
  String theFile; //the file stored as a string
  bool hasFile; //currently contains a file

  //CI: thefile is a pointer to a String class that has all standard
  //    attributes and memory allocations


  //Pre:  Integer index for starting the search,
  //      and the character to search for
  //Post: The number of characters from [start, char)
  int countToNextChar(int start,  char ch);

 public:

  // ========================================
  //             Constructors
  // ========================================

  //Default Constructor
  //Pre:  
  //Post: theFile is initialized in memory
  File();

  //Pre:  An array of characters that is the filename is given
  //Post: theFile is initialized in memory and filled
  File(char * fileName);

  //Pre:  The file is given as a String class
  //Post: theFile is initialized in memory and filled
  File(const String & fileName);

  // ========================================
  //             Accessors
  // ========================================

  // Pre:  
  // Post: Return bool value hasFile
  bool fileExists(){return(hasFile);};

  //Pre:  
  //Post: returns if a file has been read in
  bool exists(){return (hasFile);}

  //Pre:  
  //Post: The length of the file in characters is returned
  int chars() const;

  //Pre:  
  //Post: The length of the file in lines is returned
  int lines() const;

  // ========================================
  //             File Input
  // ========================================

  // Pre:  filename is a defined string
  // Post: The file is read in given the current stored name
  void readFile();

  //Pre: The filename is given as a character array
  //Post: theFile is filled with the characters from the file
  void readFile(char * fileName);

  // ========================================
  //             File Output
  // ========================================

  // Pre:  null is a character
  // Post: The file is written to in append mode
  void write(char null);

  //Pre:  
  //Post: The current file is written to the specified location
  void write();

  //Pre:  splitFile is an array of character arrays to be written
  //      string-per-line, l is the lenght of splitFile
  //Post: The current file is written to the specified location
  void write(char ** splitFile, int l);

  // ========================================
  //             Modifiers
  // ========================================

  //Pre:  newFile is defined
  //Post: theFile is set to be newFile
  void set(String & newFile);

  //Pre:  
  //Post: Deletes the currently stored String, and re initializes it
  void deleteFile();

  // ========================================
  //             Operations
  // ========================================

  //Pre:  The array of characters to be filled, start & stop are
  //      indices in theFile
  //Post: The given array is filled with values from start to stop
  void fillArray(char * array, int start, int stop) const;

  // Pre:  
  // Post: A new array of exact size is built in heap and returned
  char * retArray()const;

  //Pre:  A character to divide the file by is given, and a reference
  //      to an integer that holds the size of the array
  //Post: An array of character arrays
  char ** splitBy(char ch, int & length) const;

  // ========================================
  //             Ostreams
  // ========================================

  // Pre:  
  // Post: The file is printed from the string class
  void print() const;

};

#endif
