Hello!

Author: Thomas Lux
Program executable: personAverage
Purpose:  Take arbitrary number of people and their ages, divide the
	  people into two groups such that the average age between the
	  two groups is minimal.

In order to compile and link this program, you only have to do one
thing!  I'm going to acquaint you with how to utilize the Makefile for
this program. Simply type "make" like such at the command line.

$ make

This will automatically link and compile all the files necessary to
run this program.  From there, to run the program, you first need to
create a file that can be used as input.  This file will contain the
name of a person on each line, followed by a space and then that
persons age.  Every new person should be on its own line.  At the end
of the file there should be one extra new line.

When you run the program, simply type at the command line:

$ ./personAverage inputFile.txt outputFile.txt

where you will type in the specific name of your input, and the name
of the file that you want the output to be saved in.  Once you run the
program everything else will be done for you, just look into the
output file and see what the results are!
