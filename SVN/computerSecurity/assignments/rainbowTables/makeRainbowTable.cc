#include <iostream>
#include <fstream>
#include "reductions.h"
#include "md5.h"

#define PASSWORD_LENGTH 6
#define EXTENSION_LENGTH 3
#define MD5_HASH_SIZE 32

using namespace std;

// Pre:  str is terminated properly
// Post: the length of str before terminator
int sizeOf(char* str){
  int size = 0;
  while(str[size] != '\0'){
    size++;
  }
  return(size);
}

// Pre:  filename is terminated, and it ends with a three letter
//       extension
// Post: The char* with the same filename and no extension
char * getFilename(char* filename){
  int length = sizeOf(filename); //get the length of the filename
  char * woutDot = new char[length+1]; //+1 for terminator
  int i=0; //integer for cycling index
  while(filename[i] != '.'){
    woutDot[i] = filename[i];
    i++;
  }
  woutDot[i] = '\0'; //terminate the filename
  return (woutDot);
}

// Pre:  password is a 6 character string of lower case alphabetic
//       characters that is properly terminated
// Post: password is changed to be the final password for this row
void runReductions(char *& password){  
  md5 hash = md5(); //init md5 hash class
  char * hashcode = new char[MD5_HASH_SIZE+1];
  //run 1st reduction
  hashcode = hash.process_string(password);
  delete(password);
  password = reduction_1(hashcode);
  //run 2nd reduction
  hashcode = hash.process_string(password);
  delete(password);
  password = reduction_2(hashcode);
  //run 3rd reduction
  hashcode = hash.process_string(password);
  delete(password);
  password = reduction_3(hashcode);
  //run 4th reduction
  hashcode = hash.process_string(password);
  delete(password);
  password = reduction_4(hashcode);
  //run 5th reduction
  hashcode = hash.process_string(password);
  delete(password);
  password = reduction_5(hashcode);
  //Running 6th reduction
  hashcode = hash.process_string(password);
  delete(password);
  password = reduction_6(hashcode);
  //since password is a reference, this fxn is complete
  //done with hashcode
  delete(hashcode);
}

// Pre:  passwords is a file full of passwords on each line, filename
//       has room for .rbw on the end of it
// Post: 
void writeRBW(ifstream & passwords, char * filename){
  int length = sizeOf(filename);
  filename[length] = '.';
  filename[length+1] = 'r';
  filename[length+2] = 'b';
  filename[length+3] = 'w';
  filename[length+4] = '\0';
  //change the extension to rbw
  ofstream rainbowFile(filename);
  char * password = new char[PASSWORD_LENGTH+1];
  char current;
  int index = 0;
  password[6] = '\0';
  while (!passwords.eof()){
    //ASSERT: at least one full password remains in the file
    passwords.get(current);
    //ASSERT: current == first char in current password
    while((current != ' ')&&(current != '\n')){
      rainbowFile << current;
      password[index] = current;
      passwords.get(current);
      index ++;
    }
    if (current == ' ') {
      passwords.get(current);

    }
    if (!passwords.eof()){
      //ASSERT: current == '\n'
      //        index == 5
      index = 0;
      runReductions(password);
      rainbowFile << ' ' << password << endl;
    }
  }
  rainbowFile.close();
  delete(password);
}

// Pre:  argc = 2, argv[1] = filename.txt where filename is the name
//       of a file that exists in the PWD and is full of passwords
// Post: filename.rbw
int main(int argc, char * argv[]){
  int status = 0; //successful execution
  ifstream passwords(argv[1]);
  char * filename = getFilename(argv[1]);
  writeRBW(passwords, filename); //write the rainbow table
  passwords.close(); //close the infile
  return(status);
}
