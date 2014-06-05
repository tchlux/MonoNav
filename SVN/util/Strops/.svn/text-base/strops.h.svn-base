#ifndef INCLUDED_STROPS

#define INCLUDED_STROPS

#define GROWTH 5	    //Growth factor for character array
                            //expansion 
#define MAX_LINE_ELEMENTS 20//Max number of args on a single line in
                            //the obj file
#define DEFAULT_ARG_SIZE 5  //Characters in the default argument


// Pre:  line is terminated
// Post: the length of line not including the terminator
int alen(const char * line);

// Pre:  old and nw are defined, old is terminated.  len(nw)>len(old)
// Post: all of old is copied into nw
void strcpy(const char * old, char * nw);

// Pre:  old is defined, old is terminated.
// Post: all of old is copied into a new character array
char * strcpy(const char * old);

// Pre:  one and two are defined and terminated
// Post: true if all characters in one are the same as in two and v.v.
bool streq(const char * one, const char * two);

// Pre:  curr is a character array, toInsert is defined
// Post: that character is inserted, new array made if necessary
char * insertChar(char * curr, int & size, char toInsert);

// Pre:  line is terminated, size is initialized outside the function
// Post: all of 'split' characters are removed from the line, the
//       elements surrounding are put into a two dimensional character
//       array 
char ** split(const char * line, char split, int & size);

// Pre:  splitLine has been filled with [size] arrays of characters
// Post: All information from splitLine is freed to memory
void delSplit(char ** splitLine, int & size);

// Pre:  splitLine has been filled with [size] arrays of characters
// Post: All information from splitLine is sent to terminal
void printSplit(const char ** splitLine, int & size);

#endif
