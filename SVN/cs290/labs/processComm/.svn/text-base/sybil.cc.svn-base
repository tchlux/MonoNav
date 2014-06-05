#include <iostream>
#include <unistd.h>    // To use the functions "fork" and "sleep"
#include <stdlib.h>    // To use the function "atoi"

using namespace std;

// This program gets two command line arguments m and n >=
// 0. Depending on the value of m, the program spawns several
// processes, which, in turn, spawn processes, etc. After having
// spawned its children, each process sleeps for n seconds before
// exiting.
int main (int argc, char * argv[]) {
  int N = atoi(argv[1]);
  int sleepTime = atoi(argv[2]);
  for (int i = 0; i < N; i++) {
    pid_t retPID = fork();  // Create a child process. The return value
			 // is 0 in the child process and the PID of
			 // the child process in the parent process.
    pid_t myPID = getpid(); // get the PID of this process.
    if (retPID == 0) {
      // this is the child process, since fork returns 0 in the child
      // process. 
      cout << "Child PID = " << myPID << " i = " << i << " and returned PID = " << retPID << endl;
    }
    else {
      // this is the parent process.
      cout << "Parent PID = " << myPID << " i = " << i << " and returned PID = " << retPID << endl;
    }
  }
  sleep(sleepTime);
  return (0);
}
