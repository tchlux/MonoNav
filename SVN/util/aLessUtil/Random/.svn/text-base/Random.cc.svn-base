#include <iostream>
#define LARGE_PRIME 17
#define A 5
#define B 11
#define RANDOM_NUMS 20 //number of iterations used for the random
                       //number generator by default

using namespace std;

int main(){
  char input;
  int seed;
  cout << "Seed? ";
  cin >> input;
  seed = (int) input;
  for(int i=0; i<RANDOM_NUMS; i++){
    seed = (seed*A + B) % LARGE_PRIME;
  }
  cout << "Final random: " << seed << endl;
  return(0);
}
