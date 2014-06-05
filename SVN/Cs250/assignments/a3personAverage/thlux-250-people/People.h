#ifndef INCLUDED_People
#define INCLUDED_People

#include <iostream>
#include "Person.h"

using namespace std;

class People{

 private:

  Person * thePeople; //Array of people
  int size; //size of group
  int max; //maximum capacity

  //CI:  (size <= max) >= 0
  //     thePeople is a pointer to an array in heapspace
  //     thePeople[0] --> thePeople[size] is defined
  //     size is the next available slot in thePeople
 public:

  //Pre:  Default constructor
  //Post: max = 0.  size = 0.  CI is satisfied
  People();

  //Pre:  oldPeople is defined and follows CI
  //Post: deep copy of oldPeople
  People(const People & oldPeople);

  //Pre:  otherGroup is defined and satisfies CI
  //Post: deep copy of otherPeopl
  People & operator=(const People & otherGroup);

  //Pre:  otherGroup is defined and satisfies CI
  //Post: New people object that has the effect of (current set) -
  //      (given set)
  People operator-(const People & otherGroup);

  // Pre:  people is defined and satisfies the CI
  // Post: An ostream object reference with information from people
  //       already inserted
  friend  ostream & operator<<(ostream & str, const People & people);

  // Pre:  A defined Person "somebody" exists and satisfies CI
  // Post: bool representing whether or not ther person exists in this
  //       People class instance
  bool contains(const Person & somebody) const;

  //Pre:  new is defined
  //Post: A copy of new is placed into thePeople, thePeople is
  //      expanded if necessary
  void add(Person & newPerson);

  // Pre:  size > 0
  // Post: the most recently added person is removed from the stack
  //       and returned 
  Person pop();

  //Pre:  
  //Post: Clear all memory, reset to default values
  void clear();

  //Pre:  0 <= ind < size
  //Post: The person at the index given
  Person index(int ind) const;

  //Pre:  
  //Post: The average age of all the people in the group
  float averageAge() const;

  // Pre:  
  // Post: Return the current size
  int getSize() const;

  //Pre:  Destructor
  //Post: thePeople is freed in memory
  ~People();
};
#endif
