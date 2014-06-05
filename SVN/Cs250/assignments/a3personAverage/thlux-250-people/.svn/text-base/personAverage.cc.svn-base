#include <iostream>
#include <fstream>
#include "peopleHelper.h"
#include "People.h"

using namespace std;

//Pre:  argc == 3 arg
//      argv[1] = valid input file
//      argv[2] = valid output file
//Post: The division of the groups of people that creates the lowest
//      difference between the averages of the two groups
int main(int argc, char * argv[]){
  int returnStatus = 0; //init return status
  char * inFileName = argv[1]; //get input file
  ifstream inFile(inFileName); //create ifstream object
  People wholeGroup = getPeople(inFile); //get whole group
  People groupOne; //Init storage for groupOne
  People groupTwo; //Init storage for groupTwo
  createEvenGroups(wholeGroup, groupOne, groupTwo); //fill the groups
  //      of people
  char * outFileName = argv[2];
  printResults(groupOne, groupTwo, outFileName); //print the results
  return(returnStatus);
}
