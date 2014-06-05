#include <iostream>

using namespace std;

#define MAXNUMBERS 10
#define SOMENUMBERS 3

// PRE:
// POST: Store the numbers 1 to 10 in an array and print them out.
int main (int argc, char * argv[]) {

  int list[MAXNUMBERS];    // Declare an array that can hold
			   // MAXNUMBERS number of int objects.

  /*
  In C++, array names are just references (pointers) to the first item
  in the array. The above declaration of list asks the system to
  allocate stack space (memory locations) for holding MAXNUMBERS
  number of integers, and the variable list contains the address to the
  first of these memory locations. Then, when list[i] is used in the
  program after i is defined, the system calculates the address of the
  memory location holding the i-th integer in the list of integers and
  list[i] is effectively the variable name for this integer. Thus, if
  MAXNUMBERS is 10, then the total number of stack space memory
  locations used are 10 words of memory for the 10 integers, and one
  word of memory for the variable list to hold the address of the
  memory location holding the first integer in the list.
  */

  int x = 0;

  for (int i = 0; i <= MAXNUMBERS; i++) {
    list[i] = x;
    x++;
  }
  //ASSERT: list[0] .. list[MAXNUMBERS-1] is defined.


  for (int i = 0; i <= MAXNUMBERS; i++) {
    cout << "list[" << i << "] = " << list[i] << endl;
  }

  return (0);

}
