#ifndef INCLUDED_Person
#define INCLUDED_Person

#include <iostream>
#include "Person.h"
#include "String.h"

using namespace std;

class Person{
  
 private:

  String name; //storage for the person's name
  int age;     //storage for the person's age

  //CI:  name is a defined String class object
  //     age is a defined integer >= 0

 public:

  //Pre:  Default constructor
  //Post: name and age are initialized but still garbage
  Person();

  //Pre:  Copy constructor
  //Post: oldPerson is defined and follows CI
  //      deep copy of oldPerson is created
  Person(const Person & oldPerson);

  //Pre:  Defined character array that is the name of the person, a
  //      space, and the age of the person ending with a terminator
  //      node
  //Post: name is set, age is set
  Person(char * nameAndAge);

  //Pre:  Defined String class that is the name of the person, a
  //      space, and the age of the person ending with a terminator
  //      node
  //Post: name is set, age is set
  Person(String & nameAndAge);

  //Pre:  otherPerson is defined and satisfies CI
  //Post: deep copy of otherPerson
  Person & operator=(const Person & otherPerson);

  // Pre:  otherPerson is defined and satisfies CI
  // Post: bool representation of whether or not the people are the
  //       same
  bool operator==(const Person & otherPerson);

  //Pre:  str is defined ostream object, person is also defined
  //Post: The reference to the ostream object is returned after
  //      information about person is added to it
  friend ostream & operator<<(ostream & str, const Person & person);

  //Pre:  Defined character array that is the name of the person
  //      ending with a terminator node
  //Post: name is set
  void setName(char * name);

  //Pre:  integer value for age >= 0 is defined
  //Post: age is saved
  void setAge(int age);

  //Pre:  
  //Post: Age is returned
  int getAge() const;

  //Pre:  Destructor
  //Post: Just in case, making sure String destructor is called
  ~Person();

};

#endif
