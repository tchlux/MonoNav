#include <iostream>
#include "People.h"
#include "Person.h"

using namespace std;

//Pre:  inFile is valid, the file has lines with people and their ages
//      space seperated
//Post: People class object filled with the people from the file
People getPeople(ifstream & inFile);

//Pre:  Three People objects, all valid.  groupOne & groupTwo are
//      empty and wholeGroup holds all people that need to be sorted
//Post: groupOne and groupTwo are filled with the combination of
//      people that has the lowest differnce between the average ages
void createEvenGroups(People & wholeGroup, People & groupOne,
		      People & groupTwo);

// Pre:  N > 0, toAdd >= 0, start >= 0, bestAveDiff >= 0, The current
//       group, the best group, and the whole group
// Post: best group is set if it is found
void recursiveHelper(int & N, People & Group, int toAdd, int start,
		     People & bGroup, float & bestAveDiff,
		     People & wholeGroup);

// Pre:  group1 and group2 are defined People class objects
// Post: The magnitude of the difference between the two averages
float computeAveDiff(People & group1, People & wholeGroup);

//Pre:  Two valid People class objects with size >= 1 person, a
//      character array that is the name of the desired output file
//Post: The results of the even split are printed to the command line
void printResults(People & groupOne, People & groupTwo, char * outFileName);
//Print all of the results in the desired format
