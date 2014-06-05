#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
  int returnStatus = 0; //normal execution

  // int x = 11; // the bit pattern will be 0s followed by 1011
  // int y = 6;  // the bit pattern will be 0s followed by 0110

  // int a = x & y; // the result is bitwise and
  // int b = x | y; // the result is bitwise or
  // int c = x ^ y; // the result is bitwise exclusive or
  // unsigned int d = ~x;    // bitwise negation.
  // cout << hex; //hexidecimal flag for cout
  // cout << "a = " << a << endl;
  // cout << "b = " << b << endl;
  // cout << dec; //decimal flag for cout
  // cout << "c = " << c << endl;
  // cout << "d = " << d << endl;

  // int X;
  // X = 0xa2;
  // cout << "X = " << X << endl;
  // cout << hex;
  // cout << "X = " << X << endl;

  // //number 13
  // int x = 6;
  // int y = x << 1; // Shift left the bit pattern in x by 1 position
  // cout << "x = " << x << " and y = " << y << endl;
  // int z = x >> 1; // Shift right the bit pattern in x by 1 position
  // cout << "x = " << x << " and z = " << z << endl;
  // cout << hex << endl;
  // cout << "x = " << x << " and y = " << y << endl;
  // cout << "x = " << x << " and z = " << z << endl;

  // //  cout << dec;
  // unsigned int a = ~x;  // a is the bitwise negation of x.
  // int b = a << 1; // Shift left the bit pattern in a by 1 position
  // cout << "a = " << a << " and b = " << b << endl;
  // int c = a >> 1; // Shift right the bit pattern in a by 1 position
  // cout << "a = " << a << " and c = " << c << endl;

  // cout << dec;
  // cout << "a = " << a << " and b = " << b << endl;
  // cout << "a = " << a << " and c = " << c << endl;

  //number 15
  unsigned int x = 0xabcd;
  unsigned int mask = 0xf; // mask is a word that is 0s and has four
  // 1s as the least significant bits.
  unsigned int result = x;
  cout << hex;
  for (int i = 0; i < 4; i++) {
    result = x & mask;
    x = x >> 4;
    cout << "i = " << i << " result = " << result << endl;
  }
  return (returnStatus);
}
