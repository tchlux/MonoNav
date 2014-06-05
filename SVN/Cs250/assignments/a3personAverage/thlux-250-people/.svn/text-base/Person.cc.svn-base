#include <iostream>
#include "Person.h"
#include "String.h"

using namespace std;

  
//Pre:  Default constructor
//Post: name and age are initialized but still garbage
Person::Person(){}

//Pre:  Copy constructor
//Post: oldPerson is defined and follows CI
//      deep copy of oldPerson is created
Person::Person(const Person & oldPerson){
  name = oldPerson.name; //get the name with string copy constructor
  age = oldPerson.age; //get age
}


//Pre:  Defined String class that is the name of the person, a
//      space, and the age of the person ending with a terminator
//      node
//Post: name is set, age is set
Person::Person(String & str){
  char * nameAndAge = str.retExactArray(); //get the char array directly
  int index = 0; //init storage for index
  char chr = nameAndAge[index]; //get current character
  name.reset(); //make sure name is empty and ready to have characters
  //              added 
  while (chr != ' '){//scan for space
    name.add(chr); //add character to na
    index ++; //increment index
    chr = nameAndAge[index]; // get next character
  }
  //ASSERT: name is now the valid name of the person
  //        index is that of the next character after the space
  index ++; //increment index 
  chr = nameAndAge[index]; //get next character
  age = 0; //set age
  while (chr != '\0'){
    age = age * 10 + ((int) chr - (int) '0'); //shift age and add new digit
    index ++; //increment index
    chr = nameAndAge[index]; //get next character
  }
  //ASSERT: age is the age of the person  
}


//Pre:  Defined character array that is the name of the person, a
//      space, and the age of the person ending with a terminator
//      node.
//Post: name is set, age is set
Person::Person(char * nameAndAge){
  int index = 0; //init storage for index
  char chr = nameAndAge[index]; //get current character
  name.reset(); //make sure name is empty and ready to have characters
  //              added 
  while (chr != ' '){//scan for space
    name.add(chr); //add character to na
    index ++; //increment index
    chr = nameAndAge[index]; // get next character
  }
  //ASSERT: name is now the valid name of the person
  //        index is that of the next character after the space
  index ++; //increment index 
  chr = nameAndAge[index]; //get next character
  age = 0; //set age
  while (chr != '\0'){
    age = age * 10 + (int) chr; //shift age and add new digit
    index ++; //increment index
    chr = nameAndAge[index]; //get next character
  }
  //ASSERT: age is the age of the person
}

//Pre:  otherPerson is defined and satisfies CI
//Post: deep copy of otherPerson
Person & Person::operator=(const Person & otherPerson){
  name = otherPerson.name; //get name
  age = otherPerson.age; //get age
  return(*this); //return the Person
}

// Pre:  otherPerson is defined and satisfies CI
// Post: bool representation of whether or not the people are the
//       same
bool Person::operator==(const Person & otherPerson){
  bool isIdentical = true;
  if (! ((otherPerson.age == age)&&(otherPerson.name == name)) ){
    //if the age and name are both not the identical
    isIdentical = false; //they are not identical
  }
  return(isIdentical); //return bool
}

//Pre:  str is defined ostream object, person is also defined
//Post: The reference to the ostream object is returned after
//      information about person is added to it
ostream & operator<<(ostream & str, const Person & person){
  str << person.name << " " << person.age << " "; //add name and age
  //and a space
  return (str); //return ostream reference
}

//Pre:  Defined character array that is the name of the person
//      ending with a terminator node
//Post: name is set
void Person::setName(char * newName){
  int index = 0; //init storage for index
  char chr = newName[index]; //get current character
  name.reset(); //make sure name is empty and ready to have characters
  //              added 
  while (chr != ' '){//scan for space
    name.add(chr); //add character to na
    index ++; //increment index
    chr = newName[index]; // get next character
  }
  //ASSERT: name is now the valid name of the person
}

//Pre:  integer value for newAge >= 0 is defined
//Post: age is saved
void Person::setAge(int newAge){
  age = newAge; //save value to age
}

//Pre:  
//Post: Age is returned
int Person::getAge() const{
  return(age);//return age
}

//Pre:  Destructor
//Post: Just in case, making sure String destructor is called
Person::~Person(){}
