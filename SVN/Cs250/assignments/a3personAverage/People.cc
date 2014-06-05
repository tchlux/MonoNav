#include <iostream>
#include "Person.h"
#include "People.h"

using namespace std;

//Pre:  Default constructor
//Post: max = 0.  size = 0.  CI is satisfied
People::People(){
  thePeople = NULL; //initialize thePeople
  max = 0; //set max to zero
  size = 0; //set size to zero
}

//Pre:  oldPeople is defined and follows CI
//Post: deep copy of oldPeople
People::People(const People & oldPeople){
  max = oldPeople.max; //get max
  size = oldPeople.size; //get size
  //  delete [] (thePeople); //delete old memory for thePeople
  thePeople = new Person[max]; //get new memory for people
  for (int i=0; i<size; i++){ //for person in oldPeople
    thePeople[i] = oldPeople.thePeople[i]; //get the person
  }
}

//Pre:  otherGroup is defined and satisfies CI
//Post: deep copy of otherPeopl
People & People::operator=(const People & otherGroup){
  max = otherGroup.max; //get max
  size = otherGroup.size; //get size
  delete [] thePeople; //delete old memory
  thePeople = new Person[max]; //get new memory for people
  for (int i=0; i<size; i++){ //for person in oldPeople
    thePeople[i] = otherGroup.thePeople[i]; //get the person
  }
  return(*this); //return the current People object
}

//Pre:  otherGroup is defined and satisfies CI
//Post: New people object that has the effect of (current set) -
//      (given set)
People People::operator-(const People & otherGroup){
  People returnPeople; //init storage for return group
  for (int i=0; i<size; i++){ //for person in current group

    if (!otherGroup.contains(thePeople[i])){ //if the person is not
      //being subtracted from the group
      returnPeople.add(thePeople[i]); //add them to the final group
    }
  }
  return (returnPeople); //return the final group
}

// Pre:  people is defined and satisfies the CI
// Post: An ostream object reference with information from people
//       already inserted
ostream & operator<<(ostream & str, const People & people){
  str << " People class: "; //Print start of group
  for (int i=0; i<people.size; i++){ //for person in thePeople
    str << people.thePeople[i]; //print the person
  }
  return (str); //return ostream
}

// Pre:  A defined Person "somebody" exists and satisfies CI
// Post: bool representing whether or not ther person exists in this
//       People class instance
bool People::contains(const Person & somebody) const{
  bool found = false; //bool for if the person has been found
  for (int i=0; ((i<size) && (!found)); i++){ //for person in thePeople
    if (thePeople[i] == somebody){ //if this is the same person
      found = true; //they have been found
    }
  }
  return (found); //return whether or not they were found
}

//Pre:  new is defined
//Post: A copy of new is placed into thePeople, thePeople is
//      expanded if necessary
void People::add(Person & newPerson){
  if (max-size <= 0){
    max = max*2 + 1; //get new max
    Person * tempPointer = thePeople; //init pointer to old array
    thePeople = new Person[max]; //get new heap space
    for (int i=0; i<size; i++){ //for person in thePeopl
      thePeople[i] = tempPointer[i];//copy the Person
    }
    delete [] tempPointer; //delete old memory
  }
  thePeople[size] = newPerson; //copy the new person
  size ++; //increment size
}

// Pre:  size > 0
// Post: the most recently added person is removed from the stack and
//       returned 
Person People::pop(){
  Person returnPerson;
  if (size > 0){ //if can be popped
    size -= 1; //decrement size
    returnPerson = thePeople[size]; //get the last person
    //possible memory leak?  the person at thePeople[size] is never
    // deleted, just no longer counted and will be overwritten
  }
  else{ //no people in thePeople
    cerr << "People.cc\nError: pop from empty People.\n";
  }
  return(returnPerson);//return the person
}

//Pre:  
//Post: Clear all memory, reset to default values
void People::clear(){
  max = 0; //reset max
  size = 0; //reset size
  delete [] thePeople; //free memory in heap, pointer now goes to
  //garbage 
  People * thePeople; //reinitialize pointer to nighting
}

//Pre:  0 <= ind < size
//Post: The person at the index given
Person People::index(int ind) const{
  return(thePeople[ind]); //return the person at the given index
}

//Pre:  
//Post: The average age of all the people in the group
float People::averageAge() const{
  float total = 0.0; //init storage for total, float to represent
  //halves 
  for (int i=0; i<size; i++){ //for person in group
    total += thePeople[i].getAge(); //add the age to the total
  }
  return(total/size); //return the average
}

// Pre:  
// Post: Return the current size
int People::getSize() const{
  return (size); //return size
}

//Pre:  Destructor
//Post: thePeople is freed in memory
People::~People(){
  delete [] thePeople; //delete stored memory for thePeople
}
