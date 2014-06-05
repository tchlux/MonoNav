#ifndef INCLUDED_CSM_H
#define INCLUDED_CSM_H


#include <string.h>
using namespace std;

//Pre:  split_string is a valid, NULL terminated split_string of
//      non-zero length.  split_string is of the form
//      "[a-zA-Z0-9]+ [a-zA-Z0-9]+"
//Post: Returns a copy of the first half of the string, up to the
//      space. 
inline char* get_first_half(char* split_string){
  string copy(split_string);
  int split_len = strlen(split_string);
  char* first_half = new char[split_len];
  
  int space_loc = copy.find_first_of(" ");
  strcpy(first_half, split_string);
  first_half[space_loc] = '\0';
  
  return first_half;
}

//Pre:  split_string is a valid, NULL terminated split_string of
//      non-zero length.  split_string is of the form
//      "[a-zA-Z0-9]+ [a-zA-Z0-9]+"
//Post: Returns the second half of the string, everything after the
//      space. 
inline char* get_last_half(char* split_string){
  string copy(split_string);
  int split_len = strlen(split_string);
  char* last_half = new char[split_len];

  int space_loc = copy.find_first_of(" ");
  copy.erase(0, space_loc + 1);
  strcpy(last_half, copy.c_str());

  return last_half;
}
#endif
