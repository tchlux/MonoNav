#include <iostream>

using namespace std;

// Pre:  asci character. bin = 9 slot array of characters
// Post: bin is filled with the binary representation of the number
void getBinary(char asci, char * bin){
  int value = (int) asci; //get integer value of asci
  int placeHolder = 7; //integer placeholder
  while (value > 0){
    for (int i=placeHolder; i>=1; i--){
      bin[i-1] = bin[i]; //move the previous values
    }
    switch(value%2){
    case 0: bin[placeHolder] = '0';
      break;
    case 1: bin[placeHolder] = '1';
    }
    value /= 2; //divide the value by 2
    placeHolder --; //move the placeholder one left
  }
}

// Pre:  binary character array is defined and length=9
// Post: Every digit is set to the character '0' with a terminator node
void resetBinary(char * binary){
  for (int i=0; i<8; i++){ //for slot in binary
    binary[i] = '0'; //reset to '0'
  }
  binary[8] = '\0'; //add terminator node
}

// Pre:  Binary number given by user
// Post: 
int main(int argc, char * argv[]){
  cout << "Type \"`\" to quit\n";
  char response; //place holder for user's response
  char * binary = new char[9]; //numerical holder for
  //binary representation of character
  cin >> response; //get user input
  //ASSERT user entered one character
  while (response != '`'){
    resetBinary(binary); //reset the binary number
    getBinary(response, binary); //get binary representation
    cout << "You gave " << response << "\nBinary is: " << binary << endl;
    cin >> response; //get new response
  }
  return(0);
}
