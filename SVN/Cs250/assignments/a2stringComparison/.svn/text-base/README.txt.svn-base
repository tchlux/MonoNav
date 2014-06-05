Program:  String match
Author:   Thomas Lux
Date:     Monday, September 30th, 2013
Hour:     1:19am
Feelings: tired, tardy


In order to compile and link this program, you can simply type 

    $ make stringMatch

at the command prompt when you are in the directory containing this
program's files.  If you are not aware, the command prompt is
called the terminal in Ubuntu Linux.  You can get to the terminal by
pressing Ctrl-Alt-t.  From there, navigate to the directory containing
all of the files for this program and then type the command above!
If you don't like to use make files that is okay.  Here is the
sequence of commands that you should run if you want to compile and
link manually.

     $ g++ -c String.cc
     $ g++ -c List.cc
     $ g++ -c FileReader.cc
     $ g++ -c helper.cc
     $ g++ -c stringMatch.cc
     $ g++ stringMatch.o helper.o FileReader.o List.o String.o -o stringMatch

In order to run the program properly, simply create a .txt file that
you can use as input with some valid strings and substring in it.  If
you don't know what 'valid' is then that's okay, the program will tell
you when you're wrong :D.  When you run the program, the proper way is
to do it is:

   $ ./stringMatch input_file.txt output_file.txt

Where input file is replaced by the name of the file that you would
like to use as input, and output file is the name of the file you
would like the results to be saved in.  What the output is, is the
location of the best matching start indices of the substrings listed
on lines 2 --> EOF (end of file) in your input file.  That means, the
program will cycle through the lines of the file starting at the
second, and try to find a match of the current line somewhere in the
first line.  The program will write whether or not a match existed,
and the location of the best match in the output file.  Good luck!
