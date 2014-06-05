#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
using namespace std;

int check_authentication(char* password){
  int auth_flag = 0;
  char password_buffer[16];

  strcpy(password_buffer, password);

  if(strcmp(password_buffer, "oxygen") == 0 ||
     strcmp(password_buffer, "nimda1") == 0){
    auth_flag = 1;
  }

  return auth_flag;
}


int main(int argc, char* argv[]){
  if(argc < 2){
    printf("Usage: %s <password>\n", argv[0]);
    return -1;
  }

  if(check_authentication(argv[1])){
    cout << "******************" << endl;
    cout << "  ACCESS GRANTED  " << endl;
    cout << "******************" << endl;
  }else{
    cout << "ACCESS DENIED" << endl;
  }
}
