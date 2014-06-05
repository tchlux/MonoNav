#include <iostream>
#include "File.h"

using namespace std;

// Pre:  Optional, command line arguments given
// Post: Tests of File class
int main(int argc, char * argv[]){
  cout << "Initializing a File class" << endl;
  File test; //test File
  char fileName[14] = {"test_file.txt"};
  cout << "File initialized and fileName created, beginning import\n";
  test.readFile(fileName);
  //  cout << "Printing the file from memory\n";
  test.print();
  cout << "Splitting by '\\n'\n\n";
  int length;
  char ** splitFile = test.splitBy('\n', length);
  cout << "Length of the split file: " << length << endl;

  for (int i = 0; i < length; i ++){
    cout << splitFile[i];
  }

  cout << "\nWriting those results to a file named 'test_out.txt'\n";
  test.write("file_out.txt", splitFile, length);

  cout << "The testing is now complete\n";
  return (0);
}
