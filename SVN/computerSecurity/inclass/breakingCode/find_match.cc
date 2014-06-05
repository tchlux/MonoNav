#include <iostream>
#include "FileReader.h"

// Pre:  password is a line with a password, a space and the md5
//       ecnryption 
// Post: Solely the md5
char * get_md5(char * password){
  int index = 0;
  int subtractValue = 0;
  char * final = new char[33];
  while (password[index] != ' '){
    index ++;
  }
  index ++;
  subtractValue = index;
  while (password[index] != '\0'){
    final[index-subtractValue] = password[index];
    index ++;
  }
  return (final);
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

int main(int argc, char * argv[]){
  int returnStatus = 0;
  FileReader inFile(argv[1]); //get the inFile
  FileReader passwd(argv[2]); //get the passwords
  int inFile_length = 0;
  int passwd_length = 0;
  char ** possibilities = inFile.splitBy('\n', inFile_length);
  char ** actual = passwd.splitBy('\n', passwd_length);
  char * word;
  char * pswd;
  cerr << "Entering the breaking process\n";
  for (int a=0; a<passwd_length; a++){
    pswd = get_md5(actual[a]);
    for (int i=0; i<inFile_length; i++){
      word = get_md5(possibilities[i]);
      if (isEqual(pswd, word)){
	cout << "Found a password:   " << actual[a] << endl;
	cout << "The compared value: " << possibilities[i] << endl;
	cout << endl;
      }
    }
  }
  return (returnStatus);
}
