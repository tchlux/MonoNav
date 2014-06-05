#include <iostream>
#include "File.h"
#include "String.h"
#include "LinkedList.h"
#include "Node.h"
#include "huffmanTree.h"
#include "icTuple.h"

#define WRONG_NUM_ARGS 1
#define MISSING_FILE 2
#define INVALID_FLAG 3
#define ENCRYPT_FLAG 1
#define DECRYPT_FLAG 2
#define ARRAY_SIZE 2
#define CHAR_INDEX 0
#define TERMINATOR_INDEX 1
#define INITIAL_OCCURANCE 1
#define BYTE_SIZE 8
#define EOF_CHAR '^'
#define ORD_0 48

typedef LinkedList<icTuple> tL;

using namespace std;

// Pre:  returnStatus and flagStatus are defined
// Post: 
void printResults(int returnStatus, int flagStatus){
  if (returnStatus == WRONG_NUM_ARGS){
    cout << "ERROR: Wrong number of args. Expected 3" << endl;
  }
  else{
    if (returnStatus == INVALID_FLAG){
      cout << "ERROR: Invalid flag for argument 2." << endl;
    }
    else{
      if (returnStatus == MISSING_FILE){
	cout << "ERROR: Proper files do not exist." << endl;
      }
      else{
	cout << "Successful execution." << endl;
      }
    }
  }
}

// Pre:  two defined char *s of equal length
// Post: bool:: these char*s are equivalent
bool isEqual(char * st1, char * st2){
  int index = 0;
  bool returnValue = true;
  while (st1[index] != '\0'){
    if (st1[index] != st2[index]){
      returnValue = false;
    }
    index ++;
  }
  return (returnValue);
}

// Pre:  length = length of args
//       flagStatus is defined, likewise for returnStatus
// Post: flagStatus and returnStatus are edited appropriately
void getFlagStatus(int length, char * args[],
		   int & flagStatus, int & returnStatus){
  if (length != 3){
    returnStatus = WRONG_NUM_ARGS;
  }
  else{
    char * flag = args[1];
    if ((isEqual(flag, "-e"))||(isEqual(flag, "-d"))){
      if (isEqual(flag, "-e")){
	flagStatus = ENCRYPT_FLAG;
      }
      if (isEqual(flag, "-d")){
	flagStatus = DECRYPT_FLAG;
      }
    }
    else{
      flagStatus = INVALID_FLAG;
    }
  }
}

// Pre:  chr is defined
// Post: The array form of that character is returned as new
char * arrayForm(char chr){
  char * array = new char[ARRAY_SIZE];
  array[CHAR_INDEX] = chr;
  array[TERMINATOR_INDEX] = '\0';
  return (array);
}

// Pre:  text is input file, occList is defined as well as occs
// Post: occList is ready to be filled
void countChars(File & inFile, tL & occList){
  char * text = inFile.retArray(); //get the file as a char array
  icTuple tup; //current tuple for comparison
  tup.setLeft(INITIAL_OCCURANCE); //set the initial occurance value
  Node<icTuple> * searchNode; //holder for the found node in LinkedList
  tup.setRight(arrayForm('^')); //set the data to the EOF symbol
  occList.addFront(tup); //add the eof to the occurance list
  for(int i=0; text[i] != '\0'; i++){
    tup.setRight(arrayForm(text[i])); //set the icTuple's
    // character array to the current character
    searchNode = occList.find(tup); //find (or don't) the given
    // tuple (character) 
    if (searchNode == NULL){ //if it doesn't exist
      occList.addFront(tup);//create a node for it
    }
    else{ //othewise it does exist
      (*searchNode)++; //increment the occurance of that character
    }
  }
  delete(text); //delete the character array of the file
}

// Pre:  huffTree is defined, occList is defined
// Post: The huffman tree is built from the occList
void buildTree(tL & occList, huffmanTree<icTuple> & huffTree){
  Node<icTuple> * curr = occList.getFront(); //grab first node
  while (curr != NULL){ //for every node in the list
    huffTree.huffAdd(curr->getData()); //add the data
    curr = curr->getNext(); //traverse
  }
}

// Pre:  fullByte is the defined current working byte
//       size is the current number of relevant bits
//       current is the current character to be compressed
//       tree is the huffman encoding tree
// Post: fullByte is filled with the appropriate bit information and
//       size is incremented accordingly to the compressed character
void fillByte(unsigned int & fullByte, int & size, char current, 
	      huffmanTree<icTuple> & tree){
  int shift_amount = 0;
  unsigned int currentByte;
  currentByte = tree.getByte(current, shift_amount);
  fullByte <<= shift_amount;
  fullByte |= currentByte;
  size += shift_amount;
}

// Pre:  tree is a defined huffman tree, inFile is the file to be
//       read, compressed file is a defined and empty string
// Post: Compressed file is filled with the compressed inFile
void compressFile(huffmanTree<icTuple> & tree, File & inFile, String & compressedFile){
  char * fileArray = inFile.retArray();
  unsigned int fullByte = 0; //excess room for writing 8 bits to file
  int size = 0; //size of the current bit pattern
  char current; //storage for current character
  cerr << "huffmanEncode.cc Line 146: Current size: "<<inFile.chars() << endl;
  for (int i=0; i < inFile.chars(); i++){
    current = fileArray[i]; //get the current character
    fillByte(fullByte, size, current, tree); //put the compressed char
    //       into 'fullByte'
    while (size >= BYTE_SIZE){ //while len(fullByte) > 8, write off
      //       characters to the file
      compressedFile.add((char) fullByte); //add the right 8 bits
      fullByte >>= BYTE_SIZE;
      size -= BYTE_SIZE;
    }
  }

  current = EOF_CHAR; //set current to the EOF specific character
  fillByte(fullByte, size, current, tree); //compress and add EOF
  while (size >= BYTE_SIZE){ //while there is more than a byte
    compressedFile.add((char) fullByte); //add the right 8 bits
    fullByte >>= BYTE_SIZE; //shift the saved bytes
    size -= BYTE_SIZE; //take one byte off the end
  }

  if (size > 0){ //if there are left over bits
    fullByte <<= (BYTE_SIZE-size); //shift left to pad w/ 0's
    compressedFile.add((char) fullByte); //add the remaining bits
  }
}

// Pre:  occList, tree and puff are well defined
// Post: The encoding information is written to puff
void writePuff(tL & occList, huffmanTree<icTuple> & tree, File & puff){  
  cout << "The tree that's gonna be written: " << endl;
  cout << tree << endl;

  String * puffFile = new String(); //create a string for holding the
  // file's contents
  Node<icTuple> * curr = occList.getFront(); //get the first
  // element in the occurance list
  icTuple temp; //storage for the current icTuple
  char character; //storage for current character
  char * charStar; //provided access to the current character
  int size = 0; //variable for size of current bit pattern
  unsigned int compression; //holder for the compressed symbols
  char bit; //holder for writing the bit to the puffFile string
  while (curr != NULL){
    temp = curr->getData(); //get the current tuple
    temp[charStar]; //set charStar to the char * stored
    // in the current Tuple
    character = charStar[0]; //get the actual character (the second
    // element is just a terminator node)
    compression = tree.getByte(character, size);
    puffFile->add(character); //add the character
    puffFile->add(' '); //add a space
    for (int i=(size-1); i>=0; i--){ //for each compression bit
      bit = (compression>>i)%2 + ORD_0;
      puffFile->add(bit); //add the character form of current bit
    }
    puffFile->add('\n'); //add a new line
    size = 0; //reset the size
    compression = 0; //reset the compressed byte
    curr = curr->getNext(); //traverse
  }
  puff.set(*puffFile); //set the full string to the file class
}

// Pre:  Will take flags and input files, then either encrypt or
//       decrypt 
// Post: The file is either encrypted or decrypted
int main(int argc, char * argv[]){
  int returnStatus = 0; //normal execution
  int flagStatus = 0;
  getFlagStatus(argc, argv, flagStatus, returnStatus);
  if ((returnStatus == 0)&&(flagStatus<3)){
    String fileName(argv[2]);
    if (flagStatus == 1){
      String & inFileName = fileName + ".txt";
      String & puffFileName = fileName + ".puff";
      String & huffFileName = fileName + ".huff";
      File inFile(inFileName); //read in the text file
      File puff(puffFileName); //open the puff file
      File huff(huffFileName); //open the huff file

      tL occList;    //Initialize [occ, char] list
      huffmanTree<icTuple> huffTree; //compression scheme tree
      String compressedFile; //final outFile contents
      countChars(inFile, occList); //fill the list
      occList.sort();  //sort the list of occurances
      buildTree(occList, huffTree); //build the tree      
      compressFile(huffTree, inFile, compressedFile);
      //get the contents of the compressed file
      writePuff(occList, huffTree, puff); //write puff file
      huff.set(compressedFile); //set the write data

      puff.write(); //write the string into the file
      huff.write(); //write the contents to the file
    }
    if (flagStatus == 2){
      cerr << "huffmanEncode.cc Line 154: " << endl;
      fileName += ".puff";
      File inFile(fileName);
      if (inFile.fileExists()){
	//body for decrypt
      }
      else {
	returnStatus = MISSING_FILE;
      }
    }
  }
  cerr << "huffmanEncode.cc Line 164: Printing results" << endl;
  printResults(returnStatus, flagStatus);
  return(returnStatus);
}
