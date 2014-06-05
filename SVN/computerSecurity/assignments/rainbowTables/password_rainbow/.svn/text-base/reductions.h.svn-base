#ifndef INCLUDED_REDUCTION_H
#define INCLUDED_REDUCTION_H

#define PASSWORD_CHARS 6
#define ALPHABET_SIZE  26
#define ASCII_A   ((int)'a')

//The number of reductions
//#define NUM_REDUCTIONS 5
#define NUM_REDUCTIONS 6

#define get_alpha_from_char(in) (char)((in & ALPHABET_SIZE) + ASCII_A)

#include <cstdlib>

#define UINT_SIZE 32
#define ONE_BYTE 8
#define PASSWORD_LENGTH 6
#define ALPHABET 26

using namespace std;

// Pre:  num is defined, amount is + for right, - for left
// Post: num is cyclically shifted the amount given
unsigned int cyclicShift(unsigned int num, int amount){
  if (amount < 0){
    num = (num >> (UINT_SIZE-amount)) | (num << amount);
  }
  else{ 
    num = (num << (UINT_SIZE-amount)) | (num >> amount);   
  }
  return(num);
}

// Pre:  hashcode is a 32 character array (33 w/ '\0') that is the hex
//       code produced by an md5 run on a password
// Post: an integer seed drawn from that md5
unsigned int makeSeed(char * hashcode){
  unsigned int seed = 0;
  for (int i=0; hashcode[i] != '\0'; i++){
    seed ^= hashcode[i];
    seed = cyclicShift(seed, ONE_BYTE);
  }
  return(seed);
}


// Pre:  hashcode is a 32 character MD5 fingerprint hex string
// Post: A pointer to a 6 character array created in stack space just
//       so that it's destructor gets called before it is used
char * reduction_1(char * hashcode){
  unsigned int seed = makeSeed(hashcode);
  srand(seed);
  char * next = new char[PASSWORD_LENGTH+1];
  next[PASSWORD_LENGTH] = '\0';
  for (int i=0; i<PASSWORD_LENGTH; i++){
    next[i] = (rand() % ALPHABET) + 'a';
  }
  return(next);
}

// Pre:  hashcode is a 32 character MD5 fingerprint hex string
// Post: A pointer to a 6 character array created in stack space just
//       so that it's destructor gets called before it is used
char * reduction_2(char * hashcode){
  unsigned int seed = makeSeed(hashcode);
  srand(seed);
  char * next = new char[PASSWORD_LENGTH+1];
  next[PASSWORD_LENGTH] = '\0';
  for (int i=0; i<PASSWORD_LENGTH/2; i++){
    next[i] = (rand() % ALPHABET) + 'a';
  }
  for (int i=PASSWORD_LENGTH-1; i>=PASSWORD_LENGTH/2; i--){
    next[i] = (rand() % ALPHABET) + 'a';
  }
  return(next);
}


// Pre:  hashcode is a 32 character MD5 fingerprint hex string
// Post: A pointer to a 6 character array created in stack space just
//       so that it's destructor gets called before it is used
char * reduction_3(char * hashcode){
  unsigned int seed = makeSeed(hashcode);
  srand(seed);
  char * next = new char[PASSWORD_LENGTH+1];
  next[PASSWORD_LENGTH] = '\0';
  for (int i=PASSWORD_LENGTH-1; i>=0; i--){
    next[i] = (rand() % ALPHABET) + 'a';
  }
  return(next);
}

char * reduction_4(char * hashcode){
  return(reduction_3(hashcode));
}

char * reduction_5(char * hashcode){
  return(reduction_1(hashcode));
}

char * reduction_6(char * hashcode){
  return(reduction_2(hashcode));
}


//This defines a type called reduction_function, which allows us to
//define function pointers for the reduction functions
typedef char* (*reduction_function)(char*);

reduction_function* get_reduction_array(){
  reduction_function* functions = new reduction_function[NUM_REDUCTIONS]; 
  
  functions[0] = (&reduction_1);
  functions[1] = (&reduction_2);
  functions[2] = (&reduction_3);
  functions[3] = (&reduction_4);
  functions[4] = (&reduction_5);
  functions[5] = (&reduction_6);


  return functions;
}

#endif

// //Reduction specific shifts
// #define R1_SHIFT       0
// #define R2_SHIFT       PASSWORD_CHARS
// #define R3_SHIFT       2 * PASSWORD_CHARS
// #define R4_SHIFT       3 * PASSWORD_CHARS
// #define R5_SHIFT       4 * PASSWORD_CHARS


// //Pre:  input fingerprint is a 32 hex character, null terminated
// //      char*. 
// //      0 <= starting_location < (32 - PASSWORD_CHARS)
// //Post: Returns a fixed length (PASSWORD_CHARS) char* of lowercase
// //      alphabetic characters, based on the input hex string.
// char* generic_reduction(char* fingerprint, int starting_location){
//   char* reduced_print = new char[PASSWORD_CHARS + 1];
//   for(int i = 0; i < PASSWORD_CHARS; i++){
//     reduced_print[i] = get_alpha_from_char(fingerprint[i +
// 						       starting_location]);  
//   }
//   reduced_print[PASSWORD_CHARS] = EOS;

//   return reduced_print;

// }

// //Pre:  fingerprint is a NULL terminated char* of non-zero length
// //Post: Returns a char*, the result of the md5 reduction of the first
// //      PASSWORD_CHARS characters of the fingerprint.
// char* reduction_1(char* fingerprint){
//   return generic_reduction(fingerprint, R1_SHIFT);
// }

// //Pre:  fingerprint is a NULL terminated char* of non-zero length
// //Post: Returns a char*, the result of the md5 reduction of the second
// //      PASSWORD_CHARS characters of the fingerprint.
// char* reduction_2(char* fingerprint){
//   return generic_reduction(fingerprint, R2_SHIFT);
// }

// //Pre:  fingerprint is a NULL terminated char* of non-zero length
// //Post: Returns a char*, the result of the md5 reduction of the third
// //      PASSWORD_CHARS characters of the fingerprint.
// char* reduction_3(char* fingerprint){
//   return generic_reduction(fingerprint, R3_SHIFT);
// }

// //Pre:  fingerprint is a NULL terminated char* of non-zero length
// //Post: Returns a char*, the result of the md5 reduction of the fourth
// //      PASSWORD_CHARS characters of the fingerprint.
// char* reduction_4(char* fingerprint){
//   return generic_reduction(fingerprint, R4_SHIFT);
// }

// //Pre:  fingerprint is a NULL terminated char* of non-zero length
// //Post: Returns a char*, the result of the md5 reduction of the fifth
// //      PASSWORD_CHARS characters of the fingerprint.
// char* reduction_5(char* fingerprint){
//   return generic_reduction(fingerprint, R5_SHIFT);
// }

//Pre:  functions reduction_1, reduction_2, and reduction_3,
//      reduction_4, and reduction_5 are in scope. 
//Post: Returns an array of function pointers:
//      RV[0] = reduction_1
//      RV[1] = reduction_2
//      RV[2] = reduction_3
//      ...

// reduction_function* get_reduction_array(){
//   reduction_function* functions = new reduction_function[NUM_REDUCTIONS]; 
  
//   functions[0] = (&reduction_1);
//   functions[1] = (&reduction_2);
//   functions[2] = (&reduction_3);
//   functions[3] = (&reduction_4);
//   functions[4] = (&reduction_5);

//   return functions;
// }


//#endif
