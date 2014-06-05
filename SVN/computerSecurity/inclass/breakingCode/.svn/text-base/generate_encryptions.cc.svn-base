#include <iostream>
#include <fstream>
#include "md5.h"
#include "Read512.h"
#include "FileReader.h"

// Pre:  password is defined and has a space on the end
// Post: the password without the space
char * rm_sp(char * password){
  int index = 0;
  while (password[index] != '\0'){
    if (password[index] == ' '){
      password[index] = '\0';
    }
    index ++;
  }
  return(password);
}


// Pre:  file name to read in, outfile name
// Post: 
int main(int argc, char * argv[]){
  FileReader inFile(argv[1]); //send the in file to the file reader
// class 
  md5 encrypter; //init md5
  int length = 0;
  char ** passwords = inFile.splitBy('\n', length);
  for (int i=0; i<length; i++){
    cout << rm_sp(passwords[i]) << " ";
    cout << encrypter.process_string(rm_sp(passwords[i]));
    cout << endl;
  }
  return(0);
}
