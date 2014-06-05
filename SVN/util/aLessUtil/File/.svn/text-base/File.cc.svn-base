#include <iostream>
#include <fstream>
#include "File.h"
#include "String.h"

using namespace std;

// ========================================
//             Private methods
// ========================================

//Pre:  Integer index for starting the search,
//      and the character to search for in theFile
//Post: The number of characters from [start, char)
int File::countToNextChar(int start, char ch){
  int curr = start; //temp place holder
  char chr = theFile[curr]; //current character
  while ((chr != ch)&&(chr != '\0')){ //current != search
    curr ++; //increment place holder
    chr = theFile[curr]; //get new character
  }
  return (curr - start); //+1 to be inclusive on start
}

// ========================================
//             Constructors
// ========================================

//Default Constructor
//Pre:  
//Post: theFile is initialized in memory
File::File(){
  hasFile = false;
}

//Pre:  An array of characters that is the filename is given
//Post: theFile is initialized in memory and filled
File::File(char * fileName){
  filename = new String(fileName);
  hasFile = false;
  readFile(fileName);
}

//Pre:  The file is given as a String class
//Post: theFile is initialized in memory and filled
File::File(const String & fileName){
  filename = new String(fileName);
  hasFile = false;
  char * newFileName = fileName.retExactArray();
  readFile(newFileName);
}

// ========================================
//             Accessors
// ========================================

//Pre:  
//Post: The length of the file in characters is returned
int File::chars() const{
  return (theFile.length());
}

//Pre:  
//Post: The length of the file in lines is returned
int File::lines() const{
  return (theFile.count('\n'));
}

// ========================================
//             File Input
// ========================================

// Pre:  filename is a defined string
// Post: The file is read in given the current stored name
void File::readFile(){
  char * fileName = filename->retExactArray();
  readFile(fileName);
}

//Pre: The filename is given as a character array
//Post: theFile is filled with the characters from the file
void File::readFile(char * fileName){
  if (hasFile){
    cout << "File has already been imported.\n To re-import, call deleteFile first and then import."
	 << endl;
  }
  else{
    ifstream inFile(fileName); //get the file
    if (inFile == NULL){ //if it exists
      cout << "Input file did not exist. Read aborted."
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

// ========================================
//             File Output
// ========================================

// Pre:  null is a character
// Post: The file is written to in append mode
void File::write(char null){
  char * outfile = filename->retExactArray(); //get the filename
  ofstream outFile(outfile, ios::app); //get the file
  if (outFile == NULL){ //if it exists
    cout << "Output file couldn't be created. Write aborted."
	 << endl;
  }//end if outFile exists
  else{
    for (int i=0; theFile[i] != '\0'; i++){
      outFile << theFile[i];
    }
  }
  outFile.close();
  
}

//Pre:  fileName is a character array properly terminated
//Post: The current file is written to the specified location
void File::write(){
  char * outfile = filename->retExactArray(); //get the filename
  ofstream outFile(outfile); //get the file
  if (outFile == NULL){ //if it exists
    cout << "Output file couldn't be created. Write aborted."
	 << endl;
  }//end if outFile exists
  else{
    for (int i=0; theFile[i] != '\0'; i++){
      outFile << theFile[i];
    }
  }
  outFile.close();
}

//Pre:  filename is a character array properly terminated, splitFile
//      is an array of character arrays to be written string-per-
//      line, l is the length of splitFile
//Post: The current file is written to the specified location
void File::write(char ** splitFile, int l){
  char * outfile = filename->retExactArray(); //get the filename
  ofstream outFile(outfile); //get the file
  if (outFile == NULL){ //if it exists
    cout << "Output file couldn't be created. Write aborted."
	 << endl;
  }//end if outFile exists
  else{
    int index; //index for cycling file
    for (int i=0; i<l; i++){
      index = 0;
      while (splitFile[i][index] != '\0'){
	outFile << splitFile[i][index];
	index ++;
      }
      outFile << '\n';
    }
  }
  outFile.close();
}

// ========================================
//             Modifiers
// ========================================

//Pre:  newFile is defined
//Post: theFile is set to be newFile
void File::set(String & newFile){
  hasFile=true;
  theFile=newFile;
}

//Pre:  
//Post: Deletes the currently stored String, and re initializes it
void File::deleteFile(){
  if (filename!=NULL){delete(filename);}
  theFile.reset(); //call reset on the file
  hasFile = false; //no file imported
}

// ========================================
//             Operations
// ========================================

//Pre:  The array of characters to be filled of length stop-start + 1
//      start & stop are indices in theFile 
//Post: The given array is filled with values from start to stop
void File::fillArray(char * array, int start, int stop) const{
  theFile.fillArray(array,start,stop);
}

// Pre:  
// Post: A new array of exact size is built in heap and returned
char * File::retArray()const{
  return(theFile.retExactArray());
}

//Pre:  A character to divide the file by is given, and a reference
//      to an integer that holds the size of the array
//Post: An array of character arrays
char ** File::splitBy(char ch, int & length) const{
  return(theFile.splitBy(ch,length));
}

// ========================================
//             Ostreams
// ========================================

// Pre:  
// Post: The file is printed from the string class
void File::print() const{
  theFile.print();
}

