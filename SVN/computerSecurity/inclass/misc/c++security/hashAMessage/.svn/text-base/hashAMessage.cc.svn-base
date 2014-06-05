#include <iostream>
#include <fstream>
#define MOD_VALUE 256 //The value to mod the file integer by


using namespace std;

// Pre:  0 < int num < 256
//       hexKey[0] - hexKey[1] is defined
// Post: hexValue is put into hexKey index 0 and 1
void getHexValues(int num, char * hexKey){

}

// Pre:  An ifsteam file object with existing file
// Post: The integer sum of all the ASCII values of the file
int getSum(ifstream & inFile){
  int sum; //storage for the sum of the file
  char chr; //storage for current character
  inFile.get(chr); //get new character
  while (!inFile.eof()){ //while not at end of file
    sum += (int) chr; //add ASCII of chr to sum
    inFile.get(chr); //get new character
  }
  return (sum);
}

// Pre:  argc = 2, argv[1] = input filename
// Post: The message in the input file as a number
int main(int argc, char * argv[]){
  int programState = 0; //normal run, no errors
  char * inFile = argv[1]; //get input file
  ifstream file(inFile); //init file
  int fileSum = getSum(file); //get the integer sum of all the file
  //  characters 
  int modSum = fileSum % MOD_VALUE; //change the fileSum into some
  //  range 
  cout << "File number: " << modSum << "\n"; //print the number
  char[3] hexValues; //init storage for the hex Values + \0
  getHexValues(modSum); //get the hexValues of the
  //  file 
  //  cout << "Hex values"

  return(programState);
}
