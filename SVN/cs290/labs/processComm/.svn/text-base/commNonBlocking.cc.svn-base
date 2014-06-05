#include <iostream>
#include <unistd.h>    // To use the functions "fork", "sleep" and "pipe"
#include <stdlib.h>    // To use the function "atoi"
#include <string.h>    // To use the function "strcmp"
#include <wait.h>      // To use the function "wait"
#include <fcntl.h>     // To use the defined constant O_NONBLOCK

using namespace std;

#define MAX 80

// PRE: readPipe is an open file descriptor. line is declared and has
//        space allocated for it. 
// POST: One message is read from the pipe. A message is
//        terminated by the end of string character. line contains the
//        message terminated by '\0'.
//        success is true if a message was read on the pipe. It is
//        false if there was nothing to read on the pipe.  
void readFromPipe (int readPipe, char line[], bool & success) {
  int i = 0;
  char ch;
  int numRead;    // to hold the return value from reading from the
		  // pipe.
  bool emptyPipe = false;
  do {
    numRead = read (readPipe, &ch, 1);  // try to read one character
			                // from the pipe.
    if (numRead == -1) {
      emptyPipe = true;
    }
    else { // something was read on the pipe.
      line[i] = ch;      
      i++;
    }
  }
  while ((ch != '\0') && (!emptyPipe));
  // End of message.
  line[i] = '\0';  // Terminate the string in line.
  success = !emptyPipe;  // success is true if the pipe was not empty.
}

// PRE: channel is a defined pipe.
// POST: Read a line from the pipe and output it, until the line read
// is "end".
void childProcess (int channel[]) {
  close (channel[1]); // close the write end of the pipe,  since we
		      // will not be writing to the pipe.
  
  bool done = false;
  int dummy = 0;     // just a variable to check if our read is blocking or non-blocking.
  char line[MAX];    // buffer to hold the characters read from the
		     // pipe.
  bool success;      // to store if a read was successful, i.e., if
		     // there was a message on the pipe.
  while (!done) {
    readFromPipe (channel[0], line, success);
    dummy++;
    if (success) { // A message was read on the pipe.
      if (!strcmp(line, "end")) {
	cout << "Chile received end. " << endl;
	done = true;
      }
      else {
	cout << "Received: " << line << " dummy = " << dummy << endl;
      }
    }
  }
  close(channel[0]);
  cout << "Child done!" << endl;
}

// PRE: channel is a defined pipe.
// POST: Read a line from the user and send it to the child terminated
//       by '\0'.
//       When the child ends, exit the program.
void parentProcess (int channel[]) {
  close (channel[0]); // close the read end of the pipe, since we will
		      // not be reading from the pipe.
  char line[MAX];
  char oneChar[1];
  bool done = false;
  while (!done) {
    cout << "> ";
    cin.getline(line, MAX);
    cout << "Read in parent : " << line << endl;
    if (!strcmp(line, "end")) done = true;
    bool lineDone = false;
    for (int i = 0; ((i < MAX) && (!lineDone)); i++) {
      oneChar[0] = line[i];
      if (line[i] == '\0') {
	lineDone = true;     // End of string character seen, so
			     // entire line has been processed.
      }
      write (channel[1], oneChar, 1); // write the character to the pipe.
    }
  }
  wait(NULL);         // wait for the child process to end.
  close (channel[1]); // Now close the write end of the pipe.
  cout << "Parent done!" << endl;
}

int main () {
  int channel[2]; // to hold the pipe read and write descriptors.
                  // channel[0] - read end of the pipe.
                  // channel[1] - write end of the pipe.

  int perror;     // to store the return value from the call to "pipe"

  // We initialise the pipe before forking the child process so that
  // both the parent and child processes have the pipe read and write
  // descriptors defined.
  perror = pipe2(channel, O_NONBLOCK);  // create the pipe.
                                        // The pipe2 function call is
                                        // similar to the pipe
                                        // function call, except it
                                        // allows us to specify
                                        // additional flags, e.g.,
                                        // O_NONBLOCK to open the pipe
                                        // in non blocking mode.

  if (perror == -1) {
    // error in creating the pipe.
    cout << "Error in creating the pipe. " << endl;
  }
  else {
    // The pipe called channel is open.
    
    int retPID = fork(); // create a child process.

    if (retPID == 0) {
      // This is the child.
      // Listen for data from the parent on the pipe and output it.
      childProcess (channel);
    }
    else {
      // This is the parent.
      // Read from the user and send the line to the child on the
      // pipe.
      parentProcess (channel);
    }
  }
}
