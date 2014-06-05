#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Pre:  
// Post: 
void incrementStats(double * observedProbs, double total_digits,
		    int curr, double & chiSum){
  double oProb = observedProbs[curr] / total_digits;
  observedProbs[curr] += 1;
  double eProp = observedProbs[curr] / total_digits;
  double chiSquared = ((oProb-eProp)*(oProb-eProp))/(eProp);
  chiSum += chiSquared;
}

// Pre:  
// Post: 
int main (int argc, char * argv[]){
  int returnValue = 0;
  ifstream piFile("digitsOfPi.txt");
  char curr;
  int digit;
  double chiSum = 0.0;
  double * observedProbabilities = new double[0,0,0,0,0,0,0,0,0,0];
  double total_digits = 0;
  curr = piFile.get();
  while (curr != '\n'){
    cout << curr;
    digit = (int) curr - (int) '0';
    total_digits ++;
    incrementStats(observedProbabilities, total_digits, digit, chiSum);
    cout << "Final chi: " << chiSum;
    curr = piFile.get();
  }
  cout << "Final chi: " << chiSum;
  cout << "Digits read: " << total_digits;
  return(returnValue);
}
