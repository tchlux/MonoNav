#include <iostream>
#include "helper.h"

using namespace std;

//Pre:  Commdan line argument(s) are passed in, at least one argument
//      is a natural number.
//Post: OS: the number of arguments
//      OS: prime factors of each natural number
//      OS: shared prime factors (if there is more than one NN)
//      error otherwise
int main (int argc, char * argv[]){
  int returnStatus = 0; // successful completion
  int * validArguments = getValidArgs(argc, argv);
  printNumArgs(argc, validArguments[0]); //print the number of args
  if (validArguments[0] > 0){ //if there are valid arguments
    computeSharedPrimes(validArguments); //Find the prime factors of
//      each valid argument, and find shared factors
    }
  else {
    cout << "Usage: ./numbers args, where at least one argument is a natural number" << endl << endl;
  }
  return (returnStatus); //return status is never utilized in this program
}
