#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
using namespace std;

int gcd(int a, int b){
  return gcd(b, a % b);
}

int main(int argc, char* argv[]){
  cout << gcd(1337, 31337) << endl;

  return 1;
}
