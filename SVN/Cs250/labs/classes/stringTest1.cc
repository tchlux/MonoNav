#include "MyString3.h"

int main () {
  MyString aString ((char *)"xyz");
  // aString has the value "xyz".
  aString.debugPrint();

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
