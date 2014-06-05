#include <iostream>
#include "reductions.h"
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
