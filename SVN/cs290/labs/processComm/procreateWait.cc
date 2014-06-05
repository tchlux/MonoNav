#include <iostream>
#include <unistd.h>    // To use the functions "fork" and "sleep"
#include <stdlib.h>    // To use the function "atoi"
#include <sys/types.h> // To have types used by the function "wait"
#include <wait.h>      // To use the function "wait".
#include <stdio.h>     // To use the function "printf"
using namespace std;

// This program gets two command line arguments m and n >= 0. The
// program spwan a child process. The parent process sleeps for m
// seconds and then gives one line of output; the child process sleeps
// for n seconds and then gives one line of output.
int main (int argc, char * argv[]) {
  int sleepParent; // the amount of sleep time for
				   // the parent.
  int sleepChild;  // the amount of sleep time for
				   // the child.
  pid_t retPID = fork();  // Create a child process. The return value
			 // is 0 in the child process and the PID of
			 // the child process in the parent process.

  if (retPID == 0) {
    // this is the child process, since fork returns 0 in the child
    // process. 
    sleepChild = atoi(argv[2]); // get the sleep time for child.
    sleep(sleepChild);
    printf("Child:  sleepParent<%d> sleepChild<%d> PID = %d\n",
	   sleepParent, sleepChild, retPID);

  }
  else {
    // this is the parent process.
    sleepParent = atoi(argv[1]); // get the sleep time for parent.
    sleep(sleepParent);
    printf("Parent: sleepParent<%d> sleepChild<%d> PID = %d\n",
	   sleepParent, sleepChild, retPID);

    // Have the parent process wait for the child process to finish.
    // The address of an int variable is sent as a parameter to the
    // function wait so that it can return the status value in the
    // parameter. 
    int waitStatus;
    pid_t retWait = wait(&waitStatus);
    // retWait, the return value from wait, is the PID of the child
    // process that exited. If wait returns due to some error, then
    // this return value is -1.
    cout << "Return value from wait = " << retWait << endl;
  }
  return (0);
}
