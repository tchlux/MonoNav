#ifndef INCLUDED_STROPS

#define INCLUDED_STROPS

#define GROWTH 5	    //Growth factor for character array
                            //expansion 
#define MAX_LINE_ELEMENTS 20//Max number of args on a single line in
                            //the obj file
#define DEFAULT_ARG_SIZE 5  //Characters in the default argument


// Pre:  line is terminated
// Post: the length of line not including the terminator
int alen(char * line){
  int length = 0;
  for (length; line[length] != '\0'; length++){}
  return (length);
};

// Pre:  old and nw are defined, old is terminated.  len(nw)>len(old)
// Post: all of old is copied into nw
void strcpy(char * old, char * nw){
  int index = 0;
  for (index; old[index]!='\0'; index++){
    nw[index] = old[index];
  }
  nw[index+1] = '\0';
};

// Pre:  one and two are defined and terminated
// Post: true if all characters in one are the same as in two and v.v.
bool streq(char * one, char * two){
  bool equal = true;
  for (int index=0;((one[index]!='\0')&&(two[index]!='\0')); index++){
    if (one[index] != two[index]){
      equal = false;
    }
  }
  return(equal);
}

// Pre:  curr is a character array, toInsert is defined
// Post: that character is inserted, new array made if necessary
char * insertChar(char * curr, int & size, char toInsert){
  int length = alen(curr);
  if (length >= size){
    size *= GROWTH;
      char * temp = new char[size];
    strcpy(curr, temp);
    delete(curr);
    curr = temp;
  }
  curr[length] = toInsert;
  curr[length+1] = '\0';
  return(curr);
};

// Pre:  line is terminated, size is initialized outside the function
// Post: all of 'split' characters are removed from the line, the
//       elements surrounding are put into a two dimensional character
//       array 
char ** split(char * line, char split, int & size){
  char ** splitLine = new char*[MAX_LINE_ELEMENTS]; //holder for line
  size = 0; //Set size equal to initial value of 0
  int argSize = DEFAULT_ARG_SIZE; //Default the argsize
  char * arg = new char[argSize]; //Create new character array for
                                  // first argument
  arg[0] = '\0'; //Terminate the character array
  for (int index=0; line[index]!='\0'; index++){ //cycle till EOL
    if ((line[index] == split)&&(alen(arg) > 0)){ //if a split was
                                                  // found and
                                                  // argument has been
                                                  // populated 
      splitLine[size] = arg; size++; //add argument, increment size
      argSize = DEFAULT_ARG_SIZE; //reset argSize to default
      arg = new char[argSize]; arg[0] = '\0'; //new array, terminate
    }
    else if (line[index] != split){ //Just add the next character
      arg = insertChar(arg, argSize, line[index]);
    }
  }
  if (alen(arg) > 0){ //Final check for last element, if it exists
    splitLine[size] = arg; //Add it in, and increment size
    size++;
  }
  else{
    delete(arg); //That argument was created for nothing
  }
  return(splitLine); //splitLine is occupied with line contents after
                     // removing all of the split characters
};

#endif
