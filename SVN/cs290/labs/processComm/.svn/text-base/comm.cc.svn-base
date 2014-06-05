#include <iostream>
#include <unistd.h>    // To use the functions "fork", "sleep" and "pipe"
#include <stdlib.h>    // To use the function "atoi"
#include <string.h>    // To use the function "strcmp"
#include <wait.h>      // To use the function "wait"
#include <stdio.h>

using namespace std;

#define MAX 80 // Max number of characters in a line given by the user
#define RESPONSE_MAX 50

// PRE: readPipe is an open file descriptor. line is declared and has
//        space allocated for it. 
// POST: One message is read from the pipe. A message is
//        terminated by the end of string character. line contains the
//        message terminated by '\0'.
void readFromPipe (int readPipe, char line[]) {
  int i = 0;
  char ch;
  do {
    read (readPipe, &ch, 1);  // try to read one character
                              // from the pipe.
    line[i] = ch;
    i++;
  } while (ch != '\0'); 
  // End of message.
  line[i] = '\0';  // Terminate the string in line.
  std::cerr << "comm.cc Line 29: " << std::endl;
}

// PRE: channel is a defined pipe.
// POST: Read a line from the pipe and output it, until the line read
// is "end".
void childProcess (int channel[], int schannel[]) {
  bool done = false;  // Program terminator
  close (channel[1]); // close the write end of the pipe
  close (schannel[0]);// Close the reading end of the other pipe
  char line[MAX];     // buffer to hold the characters read from the pipe.
  char response[MAX]; //Holder for child response
  char oneChar[1];    // For writing the response to the pipe
  while (!done) {
    readFromPipe (channel[0], line);
    if (!strcmp(line, "end")) done = true;
    else {
      sprintf(response, "Child received: %s", line);
      for (int i=0; ((i<MAX) && (response[i]!='\0')); i++) {
	oneChar[0] = response[i];
	write (schannel[1], oneChar, 1); // write the character to the pipe.
      }
      write(schannel[1], "\0", 1);
      // write (schannel[1], response, RESPONSE_MAX);
    }
  }
  close(channel[0]);
  close(schannel[1]);
}

// PRE: channel is a defined pipe.
// POST: Read a line from the user and send it to the child terminated
//       by '\0'.
//       When the child ends, exit the program.
void parentProcess (int channel[], int schannel[]) {
  bool done = false;
  close (channel[0]); // close the read end of the pipe
  close (schannel[1]);// Close write end of other pipe
  char line[MAX];
  char oneChar[1];
  while (!done) {
    cout << "> ";
    cin.getline(line, MAX);
    //    cout << "Read in parent : " << line << endl;
    if (!strcmp(line, "end")) done = true;
    for (int i=0; ((i < MAX) && (line[i]!='\0')); i++) {
      oneChar[0] = line[i];
      write (channel[1], oneChar, 1); // write the character to the pipe.
    }
    write(channel[1], "\0", 1);
    readFromPipe (schannel[0], line);
    printf("Parent hears: %s", line);
    //      cout << "Received: " << line << " dummy = " << dummy << endl;
  }
  wait(NULL);         // wait for the child process to end.
  close (channel[1]); // Now close the write end of the pipe.
  close (schannel[0]);
  cout << "Parent done!" << endl;
}

int main () {
  int channel[2]; // to hold the pipe read and write descriptors.
                  // channel[0] - read end of the pipe.
                  // channel[1] - write end of the pipe.

  int schannel[2];

  int perror;     // to store the return value from the call to "pipe"
  int sperror;

  // We initialise the pipe before forking the child process so that
  // both the parent and child processes have the pipe read and write
  // descriptors defined.
  perror = pipe(channel);  // create the pipe.
  sperror = pipe(schannel);

  if ((perror == -1)||(sperror == -1)) {
    // error in creating the pipe.
    cout << "Error in creating the pipe. " << endl;
  }
  else {
    // The pipe called channel is open.
    
    int retPID = fork(); // create a child process.

    if (retPID == 0) {
      // This is the child.
      // Listen for data from the parent on the pipe and output it.
      childProcess (channel, schannel);
    }
    else {
      // This is the parent.
      // Read from the user and send the line to the child on the
      // pipe.
      parentProcess (channel, schannel);
    }
  }
}
