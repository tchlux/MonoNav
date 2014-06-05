#include <iostream>

#define BASE_TEN 10 //Used for reading in a base ten number
#define BASE_SIXTEEN 16 //Used for hex conversion
#define BASE_TWO 2 //Used for binray conversion

#define BIN_PER_HEX 4 //Binary digits per hex digit

#define INT_DIGITS 9 //Max number of digits in user input
#define HEX_DIGITS 8 //Only display this many hex digits
#define BIN_DIGITS BIN_PER_HEX * HEX_DIGITS //Display this many digits

#define MAX_BINARY 2147483648 //Max binary number acceptable

#define ESCAPE_CHAR 'q' //Character for ending loop
#define ORD_0 (int) '0' //Used to shift characters to appropriate rng
#define ORD_a (int) 'a' //Used to get to the alphabet

using namespace std;

// Pre:  num is defined, power >= 0
// Post: num ^ (power) is returned
int pow(int num, int power){
  int final = 1;
  for (; power>0; power--){
    final *= num;
  }
  return (final);
}

// Pre:  0 <= num < 16
// Post: The appropriate hex character is returned
char getHex(int num){
  char hex;
  if (num < BASE_TEN){ // 0 <= num < 10
    hex = (char) (num + ORD_0); //get numerical character form
  }
  else{ // 10 <= num < 16
    hex = (char) ((num%BASE_TEN) + ORD_a); //get the alpha character
  }
  return (hex); //return the character
}

// Pre:  charNum is a character array that is terminated,
//       -> no spaces in the number, strictly chars '0'-'9' or '-'
// Post: The integer form of the number given in the char array
//       -> if any digit is '-' then the result will *= -1
int charToNum(char * charNum){
  int num = 0; //The final return number
  bool negative = false; //If the return number is negative
  for (int digit=0; charNum[digit] != '\0'; digit++){
    if (charNum[digit] == '-'){
      negative = true;
    }
    else{
      num *= BASE_TEN; //Shift the number
      num += (int) charNum[digit] - ORD_0;
    }
  }
  if (negative){ //if the number is negative
    num *= -1; //times the final result by -1
  }
  return(num);
}

// Pre:  num is an integer, bin is of length BIN_DIGITS + 1
// Post: The number's binary form is stored in bin
void numToBin(int num, char * bin){
  bool negative = num<0; //if the number is negative
  if (negative){ num += (MAX_BINARY); } //appropriately flip num
  int currDigit; //Holder for the current binary digit (up to 2)
  for (int digit=1; digit<=BIN_DIGITS; digit++){
    currDigit = num % BASE_TWO; //Get digits right to left
    bin[BIN_DIGITS-digit] = (char) ((num % BASE_TWO) + ORD_0);
    num /= BASE_TWO; //Divide the number to shift it
  }
  if (negative){ bin[0] = '1'; } //Sign bit flipped
}

// Pre:  bin & hex are of length BIN_DIGITS & HEX_DIGITS respectively
// Post: the binary form is converted to hexidecimal
void binToHex(char * bin, char * hex){
  int num; //num rep of current 4 binary digits
  for (int binDigit=0; bin[binDigit]!='\0'; binDigit+=BIN_PER_HEX){
    num = 0; //reset numerical value of current 4 binary digits
    for (int currBin=0; currBin<BIN_PER_HEX; currBin++){
      if (bin[binDigit+currBin] == '1'){ //if this power of 2 is true
	num += pow(BASE_TWO, (BIN_PER_HEX-1)-currBin); //-1 for 0 pow
      }
    }
    hex[binDigit/BIN_PER_HEX] = getHex(num); //save the hex of the 4
  }
}

// Pre:  a number character array
// Post: The binary representation as a char * and the hex rep
char ** numToBin(char * charNum){
  int num; // integer form of user input
  num = charToNum(charNum); //Get the numerical form  
  char ** final = new char*[2]; //info on the number storage
  final[0] = new char[BIN_DIGITS+1]; //allocate memory for arrays
  final[1] = new char[HEX_DIGITS+1];
  final[0][BIN_DIGITS] = '\0'; //set terminators for arrays
  final[1][HEX_DIGITS] = '\0';
  numToBin(num, final[0]); //Get the binary form of the number
  binToHex(final[0], final[1]); //Get the hex rep of the bin number
  return (final); //return the final information
}

// Pre:  none
// Post: Enter a loop that shows the binary and hex representations of
//       the number the user inputs
int main(){
  int status = 0; // Normal return status
  char userInput[INT_DIGITS+2]; //+1 for terminator, +1 for negative

  int num; // integer form of user input
  char hex[HEX_DIGITS+1]; //hex form of input +1 for terminator
  char bin[BIN_DIGITS+1]; //binary of input ''
  hex[HEX_DIGITS] = '\0'; //Set the terminator for the hex char array
  bin[BIN_DIGITS] = '\0'; //'' for the binary number

  cout << "Enter a number, max digits: " << INT_DIGITS << endl;
  cout << "Or type '"<<ESCAPE_CHAR<<"' to quit" << endl << endl;;
  cin >> userInput; //Get a number from the user
  while (userInput[0] != ESCAPE_CHAR){ //Main loop

    num = charToNum(userInput); //Get the numerical form
    numToBin(num, bin); //Get the binary form of the number
    binToHex(bin, hex); //Get the hex representation of the binary num
    
    cout << "Binary form: 0b" << bin << endl;
    cout << "Hex form:    0x" << hex << endl;

    cin >> userInput; //Get a number from the user
  }

  return(status);
}

    // numToHex(num, hex); //Get the hex form of the number

// // Pre:  num is an integer of no more than INT_DIGITS digits
// // Post: The character array 'hex' is filled with the appropriate hex
// //       character 
// void numToHex(int num, char * hex){
//   bool negative = false;
//   if (num < 0){ //if the number is negative
//     num *= -1; //Make the number positive for conversion
//     negative = true; // set negative true so it is flipped
//   }
//   int currDigit; //Holder for the current hex digit (up to 16)
//   for (int digit=1; digit<=HEX_DIGITS; digit++){
//     currDigit = num % BASE_SIXTEEN; //Get digits right to left
//     hex[HEX_DIGITS-digit] = getHex(currDigit);
//     num /= BASE_SIXTEEN; //Divide the number to shift it
//   }
// }
