#include <iostream>
#define ORDZERO 48

using namespace std;

//Pre:  Postive number is given
//Post: floor of square root of num
int squareRoot(int num);

//Pre:  An integer
//Post: Boolean for if the number is prime
bool isPrime(int num);

//Pre:  A string of a natural number
//Post: The natural number is returned as an integer
int toNaturalNumber(char * strNum);

//Fxn:  This function will print out prime numbers to the terminal
//      counting up from an optional start value
//Pre:  Optional command line argument, first arg is natural number to
//      start counting from
//Post: OS: prime numbers
int main (int argc, char * argv[]){
  int primeFinder = 2; //initialize prime number finder
  if (argc > 1){
    cout << "Got your argument, turning it into a number :)" << endl;
    primeFinder = toNaturalNumber(argv[1]);// if arg is given, attempt to get
//      the starting number
  }
  cout << "The process of finding prime numbers begins" << endl;
  cout << "By the way, it can't be stopped.." << endl;
  cout << "Remember, each '.' is a number that wasn't prime" << endl;
  while (true){
    if (isPrime(primeFinder)){
      cout << endl << "Prime number: " << primeFinder << endl;
      }
    primeFinder ++;
    cout << ".";
  }
}

//Pre:  Postive number is given
//Post: floor of square root of num
int squareRoot(int num){
  int check = 1;
  while (check*check < num){
    check ++;
  }
  //Assert: check squared is the first value squared larger than
  //number
  check --; //decrement the number to make the floor
  return (check);
}

//Pre:  An integer
//Post: Boolean for if the number is prime
bool isPrime(int num){
  int check = 2; //Current check
  int cap = squareRoot(num); //cap for stopping the prime checker
  while (check <= cap){
    if (num % check == 0){
      return false; //divisor was found, not prime
    }
    check ++;
  }
  return true; //no divisors found
}

//Pre:  A string of a natural number
//Post: The natural number is returned as an integer
int toNaturalNumber(char * strNum){
  int current = 0; //init index in string
  int number; //storage for final number
  int digit; //storage for current digit
  while (strNum[current] != '\0'){
    digit = (int) strNum[current];
    digit -= ORDZERO;
    number = number*10 + digit;
    current ++;
  }
  return (number);
}
