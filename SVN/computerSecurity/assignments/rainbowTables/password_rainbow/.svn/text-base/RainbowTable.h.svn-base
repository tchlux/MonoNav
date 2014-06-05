/**********************************************************************
 * Author:  Scotty Smith
 *
 * Purpose: Defines a Rainbow Table class, which can be used to
 *          crack passwords.
 **********************************************************************/

#ifndef INCLUDED_RAINBOWTABLE_H
#define INCLUDED_RAINBOWTABLE_H

#include <fstream>
#include <iostream>
using namespace std;


//rainbow_table indicies
#define START_INDEX  0
#define END_INDEX    1
#define ROW_SIZE     2

#define DEFAULT_SIZE 10

//Maximum line size for the operator>>
#define MAX_LINE_LEN 100

class RainbowTable{
  //CLASS INVARIANT: rainbow_table is a list of "tuples", char*'s that
  //                 represent the start and end points of hash
  //                 chains.  It's length is always curr_size large.
  //                 curr_size > 0.

 private:
  //Holds the entirety of the rainbow table.  Likely to be MASSIVE.
  char*** rainbow_table;

  //The number of rows currently used in the rainbow_table.
  int num_rows;

  //The current size in memory, in number of rows of the table.
  int curr_size;

  //Pre:  this is a well defined RainbowTable object.
  //Post: Doubles the number of available rows in the rainbow_table.
  void expand_table();

  //Pre:  rainbow_table instance variable has a number of rows set at
  //      curr_size. 
  //      starting_loc is a valid integer,
  //      0 <= starting_loc < curr_size.  Default is 0.
  //Post: Makes sure that every row in the rainbow_table has two
  //      entries.
  void initialize_rows(int starting_loc = 0);

 public:
  //Pre:  None
  //Post: Initializes the rainbow_table instance variable.
  RainbowTable();

  //Pre:  this is a valid RainbowTable object.
  //      start_chain and end_chain are valid, NULL terminated char*'s
  //      of a non-zero length;
  //Post: adds start_chain and end_chain to the rainbow_table instance
  //      variable.  Will expand the rainbow_table as necessary.
  void add(char* start_chain, char* end_chain);

  //Pre:  index is an integer, 0 <= index < num_rows.
  //Post: Returns the chain starting location from that row in
  //      rainbow_table. 
  const char* get_start(int index);

  //Pre:  index is an integer, 0 <= index < num_rows.
  //Post: Returns the chain ending char* from that row in
  //      rainbow_table. 
  const char* get_end(int index);

  //Pre:  password is a char* of length PASSWORD_CHARS
  //Post: Returns an integer index, the index of the hash chain password
  //      was found in.  It is -1 if it is not found
  int password_in_table(char* password) const;

  //Pre:  in is a reference to a valid ifstream object.
  //      data_loc is a reference to a valid RainbowTable object
  //Post: Reads lines from in, storing them in data_loc until the
  //      input stream hits EOF.
  //      Returns the ifstream, but that is pointless since the
  //      ifstream will be at EOF.
  friend ifstream& operator>>(ifstream& in, RainbowTable& data_loc);

  //Pre:  parameter num_rows is accessible
  //Post: Returns the number of rows in the rainbow table
  int get_size() const{
    return num_rows;
  }
};



#endif
