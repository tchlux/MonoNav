/**********************************************************************
 * Author:  Scotty Smith
 *
 * Purpose: Defines a Rainbow Table class, which can be used to
 *          crack passwords.
 **********************************************************************/

#include "RainbowTable.h"
#include "custom_string_methods.h"
#include "constants.h"
#include <string.h>
#include <iostream>
using namespace std;

/* BEGIN PRIVATE FUNCTIONS */

//Pre:  this is a well defined RainbowTable object.
//Post: Doubles the number of available rows in the rainbow_table.
void RainbowTable::expand_table(){
  char*** old_table = rainbow_table;
  int old_size = curr_size;
  
  curr_size *= 2;
  rainbow_table = new char**[curr_size];
  initialize_rows(old_size);

  for(int row = 0; row < old_size; row++){
    rainbow_table[row] = old_table[row];
  }
  
  delete[] old_table;
}

//Pre:  rainbow_table instance variable has a number of rows set at
//      curr_size.
//      starting_loc is a valid integer,
//      0 <= starting_loc < curr_size.  Default is 0.
//Post: Makes sure that every row in the rainbow_table has two
//      entries.
void RainbowTable::initialize_rows(int starting_loc){
  for(int i = starting_loc; i < curr_size; i++){
    rainbow_table[i] = new char*[ROW_SIZE];
  }
}

/* END PRIVATE FUNCTIONS */

/* BEGIN PUBLIC FUNCTIONS */
//Pre:  None
//Post: Initializes the rainbow_table instance variable.
RainbowTable::RainbowTable(){
  curr_size = DEFAULT_SIZE;
  num_rows = 0;
  rainbow_table = new char**[curr_size];
  initialize_rows();
}

//Pre:  this is a valid RainbowTable object.
//      start_chain and end_chain are valid, NULL terminated char*'s
//      of a non-zero length;
//Post: Copies start_chain and end_chain to the rainbow_table instance
//      variable.  Will expand the rainbow_table as necessary.
void RainbowTable::add(char* start_chain, char* end_chain){
  if(num_rows == curr_size){
    expand_table();
  }
  int start_len = strlen(start_chain);
  char* local_start = new char[start_len];
  strcpy(local_start, start_chain);
  rainbow_table[num_rows][START_INDEX] = local_start;

  int end_len = strlen(end_chain);
  char* local_end = new char[end_len];
  strcpy(local_end, end_chain);
  rainbow_table[num_rows][END_INDEX] = local_end;

  num_rows++;
}

//Pre:  index is an integer, 0 <= index < num_rows.
//Post: Returns the chain starting location from that row in
//      rainbow_table. 
const char* RainbowTable::get_start(int index){
  return rainbow_table[index][START_INDEX];
}

//Pre:  index is an integer, 0 <= index < num_rows.
//Post: Returns the chain ending char* from that row in
//      rainbow_table. 
const char* RainbowTable::get_end(int index){
  return rainbow_table[index][END_INDEX];
}

//Pre:  password is a char* of length PASSWORD_CHARS
//Post: Returns an integer index, the index of the hash chain password
//      was found in.  It is -1 if it is not found
int RainbowTable::password_in_table(char* password) const{
  int found_index = NOT_FOUND;
  string password_string = password;
  for(int i = 0; i < num_rows && found_index == NOT_FOUND; i++){
    string rainbow_string = rainbow_table[i][END_INDEX];
    if(rainbow_string == password_string){
      found_index = i;
    }
  }

  return found_index;
}

//Pre:  in is a reference to a valid ifstream object.
//      data_loc is a reference to a valid RainbowTable object
//Post: Reads lines from in, storing them in data_loc until the
//      input stream hits EOF.
//      Returns the ifstream, but that is pointless since the
//      ifstream will be at EOF.
ifstream& operator>>(ifstream& in, RainbowTable& data_loc){
  char* line = new char[MAX_LINE_LEN];

  while(!in.eof()){
    in.getline(line, MAX_LINE_LEN);
    char* first_half = get_first_half(line);
    char* second_half = get_last_half(line);
    data_loc.add(first_half, second_half);
  }

  delete[] line;

  return in;
}


/* END PUBLIC FUNCTIONS */
