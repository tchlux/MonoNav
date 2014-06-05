#ifndef INCLUDED_File
#define INCLUDED_File
#define DEFAULT_BUFFER_SIZE 50
#define MISSING_FILE "ERROR: Given file did not exist.  Read aborted"

#include <fstream>

class File{
  //CI: filename is well defined, fileBuffer never
  //    contains more than

private:

  int bufferSize; //max size of the fileBuffer
  int fill; //current chars in buffer
  char * fileBuffer; //location for holding temporary interactions
                     // with the ofstream
  char * filename; //the name of the file
  ifstream inFile; //for holding the inFile stream
  ofstream outFile; //for holding the outFile stream
  bool hasFile; //the file existed (for telling if read or write)

  // Pre:  string is defined and terminated
  // Post: The size of string (excluding terminator node) is returned
  //       as an integer
  int sizeOf(char * string){
    int size;
    for (size=0; string[size] != '\0'; size++){}
    return(size);
  };

  // Pre:  string is defined and terminated
  // Post: A pointer to a copy of the given char* is returned
  char * copy(char * string){
    size = sizeOf(string); //get the size of the string
    char * final = new char[size+1]; //+1 for terminator
    for (int i=0; string[i]<=size; i++){
      final[i] = string[i];
    }
    return(final);
  };

  // Pre:  
  // Post: buffer is read full again
  void fillReadBuffer(){
    while ((!inFile.eof())&&(fill<bufferSize)){
      //while not at end of file & buffer not full
      inFile.get(fileBuffer[fill]); //get new character
      fill++;
    }
  };

  // Pre:  
  // Post: buffer is written to file
  void writeBuffer(){
    while (fill>0){
      fill--;
      outFile << fileBuffer[fill];
    }
  };

public:

  // ========================================
  //             Constructors
  // ========================================

  //Default Constructor
  //Pre:  
  //Post: Everything set to default value
  File(){
    bufferSize = DEFAULT_BUFFER_SIZE;
    fileBuffer = new char[bufferSize];
    hasFile = false;
  }

  //Pre:  An array of characters that is the filename is given
  //Post: theFile is initialized in memory and filled
  File(char * fileName){
    bufferSize = DEFAULT_BUFFER_SIZE;
    fileBuffer = new char[bufferSize];
    filename = copy(fileName);
    hasFile = false;
  };

  // ========================================
  //             Accessors
  // ========================================

  // Pre:  
  // Post: Return true if using ifstream
  bool in(){return(hasFile);};

  // Pre:  
  // Post: Return true if using ofstream
  bool out(){return(!hasFile);};

  // ========================================
  //             File Input
  // ========================================

  // Pre:  filename is defined and filename exists in the PWD
  // Post: ifstream opened, hasFile set to true
  void read(){
    if (!(inFile.is_open())){ //if the file is not already open
      inFile.open(filename); //get the file
    }
    if (inFile == NULL){ //if it doesn't already exist
      cout << MISSING_FILE << endl;
    }//end if inFile exists
    else{
      hasFile = true; //file exists
      fillReadBuffer(); //fill the buffer
    }
  };

  // ========================================
  //             File Output
  // ========================================

  //Pre:  output is defined and properly terminated
  //Post: The current file is written to the specified location
  void write(char * output){
    for (int i=0; output[i] != '\0'; i++){
      if (fill == bufferSize){
	writeBuffer();
      }
      fileBuffer[fill] = output[i];
      fill++;
      while (fill<bufferSize){


      }

    }
  };

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

  // Pre:  
  // Post: set to append mode
  bool setAppend(){outFile.openmode=ios_base::app;};

  // Pre:  
  // Post: set to write mode, will overwrite existing files
  bool setOverwrite(){outFile.openmode=ios_base::trunc;};

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

  // Pre:  
  // Post: Anything that could have been left in memory is closed
  ~File(){
    if (inFile.is_open()){
      inFile.close();
    }
    if (outFile.is_open()){
      outFile.close();
    }
    if (fileBuffer != NULL){
      delete(fileBuffer);
    }
    if (filename != NULL){
      delete(filename);
    }
  };

};

#endif
