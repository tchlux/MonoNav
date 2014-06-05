#include <iostream>
#include <fstream>
#include "peopleHelper.h"
#include "People.h"
#include "Person.h"
#include "String.h"
#include "mymath.h"

using namespace std;

//Pre:  inFile is valid, the file has lines with people and their ages
//      space seperated
//Post: People class object filled with the people from the file
People getPeople(ifstream & inFile){
  People wholeGroup; //storage for the whole group
  String line; //holder for each line
  char chr; //storage for current char
  while (! inFile.eof()){
    chr = inFile.get(); //get single character
    while ((chr != '\n')&&(!inFile.eof())){
      line.add(chr); //add character to string
      chr = inFile.get(); //get single character
    }
    if (line.length() > 0){ //if a line was read in (not just \n)
      Person newGuy(line); //get the new person
      wholeGroup.add(newGuy); //add the person to the group
      line.reset(); //reset the values inside string
    }
  }
  return (wholeGroup); //return the group of people
}

//Pre:  Three People objects, all valid.  groupOne & groupTwo are
//      empty and wholeGroup holds all people that need to be sorted
//Post: groupOne and groupTwo are filled with the combination of
//      people that has the lowest differnce between the average ages
void createEvenGroups(People & wholeGroup, People & groupOne,
		      People & groupTwo){
  int N = wholeGroup.getSize(); //get length of wholeGroup
  People Group; //current group
  int toAdd = N-1; //the amount of people that need to be added
  int start = 0; //the start index to use to get the next person
  People bGroup; //the best group found so far
  //TODO: SET MAX AGE
  float bestAveDiff = 100000; //The smallest average difference found
  for (; toAdd > (N/2); toAdd --){
    recursiveHelper(N, Group, toAdd, start, bGroup, 
		    bestAveDiff, wholeGroup);
  }
  groupOne = bGroup;//set GroupOne
  groupTwo = wholeGroup-bGroup;//set GroupTwo
}

// Pre:  Two People objects defined, satisfying CI
// Post: The average difference between group and the remaining
//       members of wholeGroup magnitude
float computeAveDiff(People & group, People & wholeGroup){
  People group2 = wholeGroup - group; //get the other group
  float ave1 = group.averageAge(); //average 1
  float ave2 = group2.averageAge(); //average 2
  float aveDiff = abs(ave1-ave2); //return the magnitude of the difference
  //  root of the square accurate to the millionths place
  return (aveDiff);
}

// Pre:  N > 0, toAdd >= 0, start >= 0, bestAveDiff >= 0, The current
//       group, the best group, and the whole group
// Post: best group is set if it is found
void recursiveHelper(int & N, People & Group, int toAdd, int start,
		     People & bGroup, float & bestAveDiff,
		     People & wholeGroup){
  if (toAdd == 0){
    float aveDiff = computeAveDiff(Group, wholeGroup);
    if (aveDiff < bestAveDiff){ // if a new best was found
      bestAveDiff = aveDiff; //bestAveDist found
      bGroup = Group;//set current group to best
    }
  }
  else{
    while(start <= N-toAdd){ //while not exhausted
      Person tempPerson = wholeGroup.index(start); //get the current person
      Group.add(tempPerson); //add new start
      recursiveHelper(N, Group, toAdd-1, start+1, //recurse
		      bGroup, bestAveDiff, wholeGroup);
      Group.pop(); //remove start from group
      start ++; //increment start
    }
  }
}

//Pre:  Two valid People class objects with size >= 1 person, a
//      character array that is the name of the desired output file
//Post: The results of the even split are printed to the command line
void printResults(People & groupOne, People & groupTwo, char * outFileName){
  ofstream outFile(outFileName);
  float aveDiff = computeAveDiff(groupOne, groupTwo);
  People finalGroup = groupTwo - groupOne;
  outFile << "Group One: " << groupOne << endl;
  outFile << "Average is " << groupOne.averageAge() << "\n\n";
  outFile << "Group Two: " << finalGroup << endl;
  outFile << "Average is " << finalGroup.averageAge() << "\n\n";
  outFile << "Average difference: " << aveDiff << endl;
  outFile.close();
}
