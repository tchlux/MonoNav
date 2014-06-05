#include <cstdio>
#include <string.h>
#include <iostream>
using namespace std;

int answer = 42;
char* question;

void contrived_function(int some_random_number){
  cout << "This is an awfully silly little program" << endl;
}

int main(int argc, char* argv[]){
  if(argc < 2){
    printf("USAGE: %s <some string argument>\n", argv[0]);
    return -1;
  }
  
  int local = 0;

  question = new char[100];
  strcpy(question, argv[1]);
  
  contrived_function(answer);

  return 1;
}
