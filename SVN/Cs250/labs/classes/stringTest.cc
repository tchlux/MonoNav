#include "MyString3.h"
// NOTE that we do not need to include iostream here since code in
// this file does not use it.

int main () {
  MyString aString;
  
  aString.add ('a');
  aString.debugPrint();

  aString.add('b');
  aString.debugPrint();

  aString.add('c');
  aString.debugPrint();

  aString.add('d');
  aString.debugPrint();

  aString.add('e');
  aString.debugPrint();

  aString.add('f');
  aString.debugPrint();

  return (0);
}
