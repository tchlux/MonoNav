#include <iostream>
#include "MyString3.h"

using namespace std;

// PRE: aString and bString are defined.
//      position = p is defined.
//      isSub is true iff bString is a substring of aString at
//      position p.
// POST: OS contains a suitable message regarding the substring
//      property of bString in aString at position p.
void printResult(MyString aString, MyString bString, 
		 bool isSub, int position) {
  bString.print();
  if (isSub) {
    cout << " is a substring of ";
  }
  else {
    cout << " is NOT a substring of ";
  }
  aString.print();
  cout << " at location " << position << endl;
}

int main () {
  MyString aString ((char *)"abcd");
  // aString has the value "abcd".
  aString.debugPrint();

  MyString bString ((char *) "bc");
  bString.debugPrint();

  for (int startIndex = 0; (startIndex < aString.length()); startIndex++) {
    printResult (aString, bString, (aString.subString(bString, startIndex)), startIndex);
  }
  return (0);
}
