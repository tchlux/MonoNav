#include <iostream>
#include <cstdlib>

#define UINT_SIZE 32
#define ONE_BYTE 8
#define PASSWORD_LENGTH 8
#define ALPHABET 26
#define HASHCODE_LENGTH 128

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
  for (int i=0; HASHCODE_LENGTH; i++){
    seed ^= hashcode[i];
    seed = cyclicShift(seed, ONE_BYTE);
  }
  return(seed);
}


// Pre:  hashcode is a 32 character MD5 fingerprint hex string
// Post: A pointer to a 6 character array created in stack space just
//       so that it's destructor gets called before it is used
char * reduction(char * hashcode){
  unsigned int seed = makeSeed(hashcode);
  srand(seed);
  char * next = new char[PASSWORD_LENGTH+1];
  next[PASSWORD_LENGTH] = '\0';
  for (int i=0; i<PASSWORD_LENGTH; i++){
    next[i] = (rand() % ALPHABET) + 'a';
  }
  return(next);
}

// Nothing in it, the functions exist
int main(int argc, char * argv[]){
  int status = 0;
  return(status);
}
