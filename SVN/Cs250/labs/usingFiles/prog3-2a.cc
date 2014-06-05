#include <iostream>
#include <fstream>   // provides the file stream objects.

using namespace std;

#define MAX_FILENAME_LENGTH 40 // maximum number of characters in a
			       // file name. 


// PRE: inFile is defined and contains an integer n followed by n data
//       integers denoted d_0 .. d_(n-1).
// POST: RV = sigma (j=0 to (n-1)) d_j.
int processInput (ifstream & inFile) {
  // Note that we are passing the parameter inFile a little
  // differently than what we have seen so far. We are using an
  // ampersand before the variable name to indicate to C++ that we are
  // passing the parameter by reference, and not by value as usual. In
  // this case, any changes made to the parameter will be reflected
  // back in the calling program. In this case, we will be reading
  // from the input file, and thus changing the input stream. Hence we
  // pass it by reference.

    int numData; // holds the number of data integers.
    inFile >> numData; 
    // ASSERT: numData = n is defined and is the number of data
    // integers. 

    // Note that we use an ifstream object just as if it were the cin
    // object.

    int sum = 0; // variable to hold the sum of the data integers.
    // ASSERT: inFile contains n data integers. We will refer to them
    //           as d_0 .. d_(n-1)
    for (int i = 0; i < numData; i++) {
      int dataInt; // variable to hold the next data integer.
      inFile >> dataInt;
      // ASSERT: inFile contains (n - i - 1) data integers.

      sum += dataInt;
      // ASSERT: sum = sigma (j=0 to i) d_j.
    }
    // ASSERT: sum = sigma (j=0 to (n-1)) d_j.

    inFile.close();  // close the input file stream.
    
    return (sum);
}

// PRE: sum = s is defined. oFileName is defined.
// POST: If the output file with name oFileName can be created, then s
//        is written to this file; otherwise, OS contains an error
//        message indicating that the output file could not be created.
void writeOutput (int sum, char oFileName[]) {
  ofstream outFile (oFileName); // Define an output stream
                                // associated with the output
				// file. 
  if (outFile != NULL) {
    // ASSERT: output file could be created
    outFile << "The sum of the data integers = " << sum << endl;
    // ASSERT: output file contains the s.
    outFile.close();
  }
  else {
    // ASSERT: output file could not be created.
    cout << "Output file could not be created" << endl;
    // ASSERT: OS contains error message for output file.
  }
}

// PRE: There are two command line arguments (in addition to the name
//        of the executable). The first specifies the name of an input
//        file. The second specifies the name of an output file.
//        The input file contains
//        integers. The first integer, n, in the file denotes the
//        number of data integers, denoted d_0 .. d_(n-1), following
//        in the file. 
// POST: If the input file exists, and the output file can be opened
//        to write, the output file (whose name is the second command line
//        argument) contains the sum of all the data integers
//        in the file is calculated.
//        If the input file does not exist, the OS contains a
//        message indicating that the input file is not present. 
//        If the output file could not be opened for writing, the OS
//        contains a
//        message indicating that the output file could not be
//        created. 
int main (int argc, char * argv[]) {

  // declare variables to hold the two file names and initialise the
  // variables from the command line arguments.
  char * inFileName = argv[1];
  char * outFileName = argv[2];

  // ASSERT: inFileName and outFileName are defined.

  ifstream inFile (inFileName); // Define an input file stream
				// associate with the input file,
				// i.e., open the file whose name is
				// in the variable inFileName as an
				// input file stream.

  if (inFile != NULL) {
    // ASSERT: input file exists.
    
    int sum = processInput(inFile);
    // ASSERT: sum = sigma (j=0 to i) d_j.

    writeOutput (sum, outFileName);
    // ASSERT: output file contains the sum of the data integers or OS
    //          contains an error message for the output file.
  }
  else {
    // ASSERT: input file does not exist or could not be opened.
    cout << "Input file does not exist or could not be opened." << endl;
  }
  
  return (0);

}


