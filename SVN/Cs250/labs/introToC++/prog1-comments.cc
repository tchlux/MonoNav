// Everything on a line after two slashes is a comment
// Also, everything between slash followed by a star and a star
// followed by a slash is a comment -- this method of commenting is
// also used below.
#include <iostream>  // This statement is called a pre-processor
                     // directive. Any statement that begins with a #
                     // sign is a pre-processor directive. In this
                     // case, i.e., in the case of the include
                     // pre-processor directive, the pre-processor
                     // "physically replaces" the directive with the
                     // contents of the library file iostream before
                     // sending the file to the compiler.
using namespace std; // C++ libraries can be
                     // arranged in namespaces. The standard, system
                     // libraries are all in the namespace called
                     // std. This statement allows us to use the
                     // objects from these libraries without having to
                     // qualify them with std. This is explained a
                     // little more below.

/* 
  This is the other way of commenting C++ programs.

  The header for the function called main that appears below is what
  we will always use for the function main. For now, do not worry
  about the formal parameters to the function; we will see what they
  are soon.

*/

/*
   We will use comments labelled by the words PRE and POST before
   every function, and comments labelled by the word ASSERT at
   suitable points in the code.
   
   PRE comments are pre-conditions for a function. These must include
   the conditions that must be satisfied by the parameters to the
   function before the function is called so that the function works
   correctly. (We will see more examples of this later.)

   POST comments are post-conditions for a function. These state
   precisely the conditions that are true about program objects after
   the function is complete.

   ASSERT comments state considions that must be true due to the code
   that has been executed so far.
*/

// PRE: 
// POST: Output stream (OS) contains the string "Hello world".
int main (int argc, char * argv[]) {

  cout << "Hello world" << endl;
  // ASSERT: OS now contains the string "Hello world"

  /*
    The library iostream provides us with system defined objects
    called cout for standard output, cin for standard input and cerr
    for standard error streams. The standard error stream is just like
    the standard output stream and both display to your terminal; we
    will see the difference between the two soon.

    The endl object is the system defined object for writing a new
    line to the output stream.

    If we had not specified the "using namespace std", we would have
    had to refer to the system defined objects as std.cout and
    std.endl

    The two less than signs together is the C++ operator for
    output. Similarly, >> is the C++ operator for input.
  */

  return (0);
  /*
    Since the return value for main is int, we must return an integer
    value from main. Usually, the value returned indicates success,
    failure, partial results, etc. from the program. 

    For our purposes, we will always return 0 from the function main.
  */
}


