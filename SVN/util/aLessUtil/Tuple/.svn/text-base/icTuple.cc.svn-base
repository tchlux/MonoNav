#include "Tuple.h"
#include "icTuple.h"
#include <iostream>

using namespace std;

//========================================
//           Private methods
//========================================

//Pre:  string is defined
//Post: The length of the character array not including the
//      terminator node is returned
int icTuple::getLength(const char * str) const{
  int size = 0;
  while (str[size] != '\0'){
    size ++;
  }
  return (size);
}

//Pre:  s1 and s2 are character arrays
//Post: the combined character array is returned
char * icTuple::combine(const char * s1,const char * s2) const{
  int size1 = getLength(s1);
  int size2 = getLength(s2);
  int size = size1 + size2;
  char * combo = new char[size+1];
  //Plus 1 for the terminator node
  for (int i=0; i<size1; i++){
    combo[i] = s1[i];
  }
  for (int i=0; i<size2; i++){
    combo[size1+i] = s2[i];
  }
  combo[size] = '\0';
  return (combo);
}

//========================================
//             Constructors
//========================================

//Pre:  
//Post: Default constructor
icTuple::icTuple() : Tuple<int,char*>() {}

//Pre:  lData is defined
//Post: lData is saved to left
icTuple::icTuple(int lData) : Tuple<int,char*>(lData) {}

//Pre:  rData is defined
//Post: rData is saved to left
icTuple::icTuple(char * rData) : Tuple<int,char*>(rData) {}

//Pre:  lData and rData are defined appropriately
//Post: saved data
icTuple::icTuple(int lData, char * rData) : Tuple<int,char*>(lData,rData) {}

//Pre:  other is defined and satisfies CI
//Post: Copy constructor executed
icTuple::icTuple(const icTuple & other){
  left = other.left;
  right = combine(other.right, "\0");
};

//========================================
//             Operators
//========================================

//Pre:  other is defined
//Post: copy of other saved here
icTuple & icTuple::operator= (const icTuple & other){
  left = other.left;
  right = combine("\0", other.right);
}

//Pre:  other is defined
//Post: bool comparison result
bool icTuple::operator> (const  icTuple & other) const{
  return((left>other.left));
}

//Pre:  other is defined
//Post: bool comparison result
bool icTuple::operator< (const icTuple & other) const{
  return((left<other.left));
}

//Pre:  other is defined
//Post: bool comparison result
bool icTuple::operator<= (const icTuple & other) const{
  return((left<=other.left));
}

//Pre:  other is defined
//Post: bool comparison result
bool icTuple::operator>= (const icTuple & other) const{
  return((left>=other.left));
}

// Pre:  other is defined
// Post: bool result, c is the only character in right
bool icTuple::operator== (const icTuple & other) const{
  bool equal = true;
  for (int i=0; ((equal)&&(right[i] != '\0')); i++){
    if (other.right[i] != right[i]){
      equal = false;
    }
  }
  return(equal);
}

// Pre:  c is an ASCII character
// Post: bool result, c is the only character in right
bool icTuple::operator== (char c) const{
  int l = getLength(right);
  return( ((l == 1) && (c = right[0])) );
}

//Pre:  other is defined
//Post: The addition of other with this is returned
icTuple & icTuple::operator+(const icTuple & other) const{
  icTuple * final = new icTuple;
  final->left = left+other.left;
  final->right = combine(right, other.right);
  return(*final);
}

//Pre:  other is defined
//Post: The other tuple is added to this
icTuple & icTuple::operator+=(const icTuple & other){
  left += other.left; //combine the ints
  right = combine(right, other.right); //get the new right
  return(*this);
}

//Pre:  
//Post: int value is incremented
icTuple & icTuple::operator++(int null){
  left ++;
  return(*this);
}

//========================================
//               Destructor
//========================================

//Pre:  
//Post: deleted
icTuple::~icTuple(){
  if(right != NULL){delete(right);}}


// ========================================
//             Accessors
// ========================================

// Pre:  c is defined
// Post: if c exists in right
bool icTuple::in(char c){
  bool found = false;
  for (int i=0; ((!found)&&(right[i] != '\0')); i++){
    if (c == right[i]){
      found = true;
    }
  }
  return(found);
}
