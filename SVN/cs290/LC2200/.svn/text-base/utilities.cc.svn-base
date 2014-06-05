#include "constants.h"
#include "utilities.h"
#include <iostream>

using namespace std;

// PRE: num is defined. 0 <= num < 16
// POST: RV is the hex character for num
char hexChar (int num) {
  char answer;
  if (num < BASETEN)
    answer = (char)(num + (int)'0');
  else
    answer = (char)((num - BASETEN) + (int)'a');
  return (answer);
}

// PRE: num is an unsigned long long int that fits in 32 bits.
// POST: RV is a string "hhhhhhhh" that is the hexadecimal
//        representaion of num.  
char * uIntToHex (unsigned long long int num) {
  char * result = new char[HEXPERWORD+1];
  for (int i = 0; i < HEXPERWORD; i++) {
    int remainder = num % BASEHEX;
    num = num / BASEHEX;
    result [HEXPERWORD - i - 1] = hexChar (remainder);
  }
  result[HEXPERWORD] = '\0';
  return (result);
}

int hexCharToInt (char h) {
  int answer;
  if ((h >= '0') && (h <= '9'))
    answer = ((int)h - (int)'0');
  else
    answer = ((int)h - (int)'a') + 10;
  return (answer);
}

long long int hex8StrToInt (char hexStr[]) {
  long long int answer = 0;
  for (int i = 0; i < 8; i++) {
    long long int temp = hexCharToInt (hexStr[i]);
    //   cout << "** " << hexStr[i] << " == " << temp << " ** ";
    temp = temp << ((8 - i -1) * 4);
    //    cout << " && " << temp << " && " << endl;
    answer = answer | temp;
    //    cout << answer << endl;
  }
  return (answer);
}
