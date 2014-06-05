#ifndef INCLUDED_helper
#define INCLUDED_helper

//Pre:  A pointer to an array of the command line arguments is given
//      and size the number of elements in the array
//Post: RV: A pointer to an array in heap space that contains each
//      valid argument as an integer, the first number in the
//      array is the number of valid arguments given
int * getValidArgs(int size, char * argv[]);

//Pre:  argc/naturalNums are given as positive integers >= 0
//Post: OS: the number of command line arguments given minus 1 for the
//          executable and the number of natural numbers given.
void printNumArgs(int argc, int naturalNums);

// Pre:  charNum is a string.
// Post: RV = true iff charNum is the character
//       representation of a natural number.
bool isNaturalNumber (char * charNum);

// PRE: charNum is the character representation of
// a natural number, say n
// POST: RV = n.
int charToNum (char * charNum);

//Pre:  An array of natural numbers is given with the first number
//      being the number of natural numbers
//Post: Each natural number and it's prime factors will be printed,
//      along with a seperate line of solely shared prime factors of
//      all the numbers given, everything created in memory is then
//      deleted
void computeSharedPrimes(int * naturalNums);

//Pre:  An integer form of a natural number is given, an array of
//      sizes (# of prime factors) to be used for storing size, and
//      the index number to reference for saving the size --> integer
//Post: All of the prime factors are returned in an array
//      No repeats of prime factors, and the smallest are first, going
//      up throughout.  The number of prime factors is saved in
//      arraySizes[indexNum]
int * findPrimeFactors(int naturalNumber, int * arraySizes, int indexNum);

//Pre:  A natural number is given that is greater than 1
//Post: RV: The smallest divisor of the number given we can assume
//      that this number will be prime itself
int smallestDivisor(int naturalNumber);

//Pre:  size of primeFactorArrays, an array of pointers to arrays of
//      prime factors, an array of sizes of prime factor arrays
//Post: RV: One pointer to an array of shared values in heap space
int * arraySharedValues(int size, int * primeFactorArrays[],
			int * arraySizes);

//Pre:  An index of an array to not be checked, the number to search
//      for, an array of pointers to other arrays, and the size of
//      that array, the size of each sub array stored in an array
//Post: RV: bool value, true if value is in all other arrays, false
//      otherwise
bool inOtherArrays(int excludeIndex, int primeNum, 
		   int * primeFactorArrays[], int size, 
		   int * arraySizes);

//Pre:  A value to search for as an integer, an array of integers, the
//      size of the array of integers
//Post: RV: value E array --> boolean
bool inArray(int value, int * array, int size);

// Pre:  num = n > 0 is defined; 
//       base = b > 0 is defined 
// Post: RV = floor (log_b (n)).
int floorLog (int num, int base) ;


//Pre:  naturalNums is the array of naturalNums with the first index
//      being the number of naturalNums present, primeFactorPointers
//      is an array of pointers to the arrays of prime factors.
//      sharedValues is an array of common prime factors to each nN,
//      arraySizes is an array of the lengths of primeFactorPointers'
//      sub-arrays and the last element is the length of sharedValues
//Post: OS: Each natural number and their prime factors, lastly the
//      common prime factors between them all.  No shared factors if
//      there are none
void print(int * naturalNums, int * primeFactorPointers[],
	   int * sharedValues, int * arraySizes);


#endif

