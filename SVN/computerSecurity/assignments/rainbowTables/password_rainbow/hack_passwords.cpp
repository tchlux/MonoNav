/**********************************************************************
 * Author:  Scotty Smith
 *
 * Purpose: Read a rainbow table, as well as a passwd file.  Attempt
 *          to crack the passwords in the passwd file using the
 *          rainbow table.
 **********************************************************************/

#include "md5.h"
#include "reductions.h"
#include "constants.h"
#include "custom_string_methods.h"
#include "RainbowTable.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define USAGE_STRING "USAGE: ./hack_passwords rainbow_table.rbw \
 passwd_file"
#define USAGE_ERR    1
#define NUM_ARGS     2
#define RBW_ARG      1
#define PWD_ARG      2
#define NUM_ELEMENTS 2


//Pre:  hash is a valid, NULL terminated char* of non-zero length.  It
//      is a 32 character HEX string.
//      chain_start is a valid, NULL terminated char* of length
//      PASSWORD_CHARS, the first element in the correct chain from a
//      rainbow table.
//      functions is an array of 3 reduction functions.
//      num_chain_iterations is an integer, the number of times to
//      iterate through the specified chain.
//Post: RV is a char* of size PASSWORD_CHARS, the password that
//      matches the users hash.
char* trace_chain(char* hash,
		  char* chain_start,
		  reduction_function* functions,
		  int num_chain_iterations){
  md5 algorithm;
  char* curr_password = new char[PASSWORD_CHARS + 1];
  string curr_hash = algorithm.process_string(chain_start);
  string requested_hash = hash;
  int reduction_index = 0;
  
  strcpy(curr_password, chain_start);
  for(int i = 0; i < num_chain_iterations; i++){
    delete[] curr_password;
    char* curr_password =
      functions[reduction_index]((char*)curr_hash.c_str()); 


    curr_hash = algorithm.process_string(curr_password);
    reduction_index++;
  }

  return curr_password;
}


//Pre:  hash is a valid, NULL terminated char* of non-zero length.  It
//      is a 32 character HEX string.
//      rainbow_table is a valid RainbowTable object.
//      functions is an array of 3 reduction functions.
//Post: Returns a vector of char*'s, all possible passwords for a
//      given entity.
vector<char*> check_hash_rainbow_style(char* hash, 
				RainbowTable rainbow_table,
				reduction_function* functions){ 
  vector<char*> passwords;
  md5 hash_alg;

  char* password = NULL;

  int rainbow_size = rainbow_table.get_size();
  char* potential_password = NULL;
  char* curr_hash = new char[HASHCODE_SIZE];

  int start_value = NUM_REDUCTIONS - 1;
  int potential_index;



  while(start_value >= 0){
    strcpy(curr_hash, hash);
    for(int num_reductions = start_value;
	num_reductions < NUM_REDUCTIONS and password == NULL;
	num_reductions++){

      if(potential_password != NULL){
	delete[] potential_password;
      }

      potential_password = functions[num_reductions]( curr_hash ); 

      delete[] curr_hash;
      curr_hash = hash_alg.process_string(potential_password);
    }

    potential_index =
      rainbow_table.password_in_table(potential_password); 

    if(potential_index != NOT_FOUND){
      char* chain_start = (char*)
	rainbow_table.get_start(potential_index); 
      password = trace_chain(hash, chain_start, functions,
			     start_value);
      vector<char*>::iterator it = passwords.end();
      passwords.insert(it, password);
    }

    start_value--;
  }

  return passwords;
}

//Pre:  passwd_file_name is a valid, NULL terminated char* of non-zero
//      length.  It refers to a file we have permission to open and
//      ready from.
//Post: Writes to stdout the usernames and passwords of passwords that
//      were broken using this method.
void process_passwords(char* passwd_file_name,
		       RainbowTable rainbow_table){
  ifstream passwd_file(passwd_file_name);
  char* line = new char[MAX_LINE_LEN];
  reduction_function* functions = get_reduction_array();

  while(!passwd_file.eof()){
    passwd_file.getline(line, MAX_LINE_LEN);
    char* username = get_first_half(line);
    char* hash = get_last_half(line);

    vector<char*> password = check_hash_rainbow_style(hash,
						      rainbow_table,
						      functions); 

    //if(password != NULL){
    for(int i = 0; i < password.size(); i++){
      cout << username << ": " << password[i] << endl;
    }
  }

  delete[] line;
}

//Pre:  argc > 2: argv[1] = rainbow table file name,
//                argv[2] = password filename
//Post: Prints the username and password for cracked passwords.
int main(int argc, char* argv[]){
  if(argc <= NUM_ARGS){
    cerr << USAGE_STRING << endl;
    return USAGE_ERR;
  }

  char* rainbow_file_name = argv[RBW_ARG];
  char* passwd_file_name  = argv[PWD_ARG];

  ifstream rainbow_file(rainbow_file_name);
  RainbowTable rainbow_table = RainbowTable();

  rainbow_file >> rainbow_table;

  process_passwords(passwd_file_name, rainbow_table);

  return 0;
}
