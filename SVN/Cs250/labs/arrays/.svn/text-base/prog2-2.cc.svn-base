#include <iostream>

using namespace std;

#define MAXNUMBERS 10000
#define SOMENUMBERS 3

// PRE: size=s > 0 is defined; inList is declared and has s number of
// elements, but the elements are not defined, 
//  i.e., inList[0]..inList[s-1] are declared, but undefined.
// POST: inList[0]..inList[s-1] are defined.
//       for all j, 0 <= j < s, inList[j] = j.
void initList (int size, int inList[]) { // Note that as a formal
                                         // parameter, you do not
                                         // specify the size of a
                                         // one-dimensional array. 
  int x = 0;

  for (int i = 0; i < size; i++) {
    // ASSERT: x = i, and i < s.
    inList[i] = x;
    // ASSERT: for all j, 0 <= j <= i, inList[j] = j.
    x++;
  }
  // ASSERT: for all j, 0 <= j < s, inList[j] = j.
}

// PRE: size=s > 0 is defined; inList is defined and has s number of
// elements, i.e., inList[0]..inList[s-1] are defined.
// POST: RV = sum(j=0..(s-1)) inList[j].
int sumList (int size, int inList[]) { // Note that as a formal
                                       // parameter, you do not
                                       // specify the size of a
                                       // one-dimensional array. 
  int answer = 0;
  for (int i = 0; i < size; i++) {
    answer += inList[i];
    // ASSERT: answer = sum (j=0..i) inList[j].
    //         i < size
  }
  // ASSERT: answer = sum (j=0..(s-1)) inList[j].
  size++;
  inList[0] = 100;
  return (answer);

}


// PRE:
// POST: Store the numbers 1 to 10 in an array and print them out.
int main (int argc, char * argv[]) {

  int list[MAXNUMBERS];    // Declare an array that can hold
			   // MAXNUMBERS number of int objects.

  initList (MAXNUMBERS, list);
  // list[0]..list[MAXNUMBERS-1] is defined.

  int numElements = MAXNUMBERS;

  // ASSERT: numElements = MAXNUMBERS > 0
  //         list[0] .. list[numElements-1] is defined.
  int mySum = sumList (numElements, list);
  // ASSERT: mySum = sum(0..(numElements-1)) list[i].

  // Note that when passing an array as a formal parameter, you
  // specify only the name of the array object.

  cout << "The sum of the numbers = " << mySum << endl;
  cout << "The number of elements: " << numElements << endl;
  cout << "Fist element of list: " << list[0] << endl;

  return (0);

}
