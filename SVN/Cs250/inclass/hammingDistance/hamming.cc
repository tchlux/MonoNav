#include <iostream>
#include "helper.h"

using namespace std;


// PRE: Two command line arguments that are natural
// numbers, say m and n
// POST: Output is the hamming distance between m
// and n, if the command line arguments are correct;
// error otherwise.
int main (int argc, char * argv[]) {
  int returnStatus = 0; // successful completion
  if (validArguments (argc, argv)) {
    computeHammingDistance (argv[1], argv[2]);
    }
    else {
      cout << "Usage: ./hammer m n, where m and n are natural numbers" << endl;
    }
    return (returnStatus);
}
