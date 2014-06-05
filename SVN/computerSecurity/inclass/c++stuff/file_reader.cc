#include <iostream>
#include <fstream>
using namespace std;

//Reads in a file and prints it out to the terminal char by char
//Pre:  The file exists
int main(){
  ifstream input("file_reader.cc");
  char curr;
  while(input){
    input >> curr;
    cout << curr << endl;
  }
  return (0);
}
