#include <iostream>
#include <unistd.h>    // To use the functions "fork" and "sleep"
#include <stdlib.h>    // To use the function "atoi"
#include <stdio.h>     // To use the function "printf"

using namespace std;

// This program gets two command line arguments m and n >= 0. The
// program spwan a child process. The parent process sleeps for m
// seconds and then gives one line of output; the child process sleeps
// for n seconds and then gives one line of output.
int main (int argc, char * argv[]) {
  int sleepParent; // get the amount of sleep time for
				   // the parent.
  int sleepChild;  // get the amount of sleep time for
				   // the child.
  pid_t retPID = fork();  // Create a child process. The return value
			 // is 0 in the child process and the PID of
			 // the child process in the parent process.
                         // The library type pid_t is used to stors
			 // process IDs.

  if (retPID == 0) {
    sleepChild = atoi(argv[2]);
    // this is the child process, since fork returns 0 in the child
    // process. 
    sleep(sleepChild);
    printf("Child:  sleepParent<%d> sleepChild<%d> PID = %d\n",
	   sleepParent, sleepChild, retPID);
      //    cout << "I am the child and returned PID = " << retPID << endl;
  }
  else {
    sleepParent = atoi(argv[1]);
    // this is the parent process.
    sleep(sleepParent);
    printf("Parent: sleepParent<%d> sleepChild<%d> PID = %d\n",
	   sleepParent, sleepChild, retPID);
      //    cout << "I am the parent and returned PID = " << retPID << endl;
  }
  return (0);
}
