#include <iostream>
#include <fstream>
#define WRONG_NUM_ARGS "ERROR USAGE NAPSACK: Expected filename"
#define NUM_ARGS 2
#define MAX_LINE_SIZE 256
#define ORD_ZERO (int) '0'

using namespace std;

// Pre:  line is properly terminated and contains only spaces and
//       numerical characters, no more than one space and two numbers
//       nums is an int array of len 2 
// Post: nums is filled with the numbers from the line
void getNums(char * line, int * nums){
  nums[0] = nums[1] = 0; //set all values to 0
  int curr = 0; //current index in line
  int num = 0; //which index in nums currently
  int temp = 0; //holder for numerical conversion
  while (line[curr] != '\0'){
    while ((line[curr] != ' ')&&(line[curr]!='\0')) {
      temp = (temp*10) + (((int) line[curr])-ORD_ZERO);
      curr++; //increment curr
    }
    curr++; //increment curr
    nums[num] = temp; //save the current value
    temp = 0; //reset temp
    num ++; //increment the current number
  }
}

// Pre:  sack is of length len and all values are defined
// Post: All the values in sack are printed
void print(int * sack, int len){
  cout << "The Sack:" << endl;
  for (int i=0; i<len; i++){
    cout << sack[i*2] << " -- " << sack[i*2+1] << endl;
  }
}


// Pre:  sack is an array of values, len is half thel length, ind is
//       weight or value
// Post: 
int get(int * sack, int len, int ind){
  int sum = 0;
  for (int i=0; i<len; i++){
    sum += sack[i*2 + ind];
  }
  return(sum);
}

// Pre:  sack is defined, integer array.  len >= 0
// Post: a pointer to a copy of sack is returned
int * copy(int * sack, int len){
  int * newSack = new int[len];
  for (int i=0; i<len; i++){
    newSack[i] = sack[i];
  }
  return(newSack);
}


// Pre:  sack -----> list of weights and values (len = numItems * 2)
//       load -----> maximum weight sack can hold integer value
//       start ----> current starting item (int > 0)
//       currSack -> index of items currently in the sack
//       index ----> next index in currSack
//       bestSack -> holder for best sack
//       bestLen --> length of best sack
// Post: 
void run(int * sack, int & load, int & items, int start,
	 int * currSack, int & index, int *& bestSack, int & bestLen){
  if (start < items){
    currSack[index*2] = sack[start];
    currSack[index*2+1] = sack[start+1];
    if (get(currSack, index+1, 0) < load){
      index ++; //the items were okay to add

      if (get(currSack, index, 1) > get(bestSack, bestLen, 1)){
	delete(bestSack);
	bestSack = copy(currSack, index);
	bestLen = index;
      }

    }
    else{
      currSack[index*2] = 0;
      currSack[index*2+1] = 0;
    }
    run(sack, load, items, start+1,
	currSack, index, bestSack, bestLen);
  }
}


// Pre:  sack is all the weights and values, len is the number of
//       items in sack (half the length) and load is the max weight
// Post: the highest value combination is recursivly searched for that
//       can fit into sack
void fillSack(int * sack, int len, int load){
  cerr << "Load: "<<load << endl;
  int * items = new int[len]; //create a sack of max size
  int index; //index in items
  int * bestSack = new int[2]; //holder for best sack
  bestSack[0] = bestSack[1] = 0; //init to 0's
  int bestLen = 1; //length of 1
  for (int start=0; start<len; start++){
    delete(items);
    items = new int[len];
    index = 0;
    run(sack, load, len, start,
	items, index, bestSack, bestLen);
  }
  cerr << "napsack.cc Line 95: Best sack: " << endl;
  print(bestSack, bestLen);
}


// Pre:  A file name to read from is given
// Post: the napsack problem is solved given this file
int main(int argc, char *argv[]){
  int status = 0; //successful execution
  if (argc != NUM_ARGS){
    cout << WRONG_NUM_ARGS << endl;
    status = 1;
  }
  if (status==0){
    char line[MAX_LINE_SIZE]; //line holder
    int * nums = new int[2]; //holder for numbers
    ifstream infile(argv[1]); //get the infile
    infile.getline(line, MAX_LINE_SIZE); //get the first line
    getNums(line, nums); //get the numbers
    int items = nums[0]; //get the number of items
    int * item_array = new int[items*2];//weight & value
    cerr << "Items: "<<items << endl;
    for (int i=0; i<items; i++){
      infile.getline(line, MAX_LINE_SIZE); //get next line
      getNums(line,nums); //get the numbers
      item_array[i*2] = nums[0]; //get the weight
      item_array[i*2+1] = nums[1]; //get the value      
    }
    print(item_array, items); //print the items to check

    infile.getline(line, MAX_LINE_SIZE); //get last line
    getNums(line,nums); //get the last number

    int maxLoad = nums[0];
    fillSack(item_array, items, maxLoad);
  }

  return(status);
}
