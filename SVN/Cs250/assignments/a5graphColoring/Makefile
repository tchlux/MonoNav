COMPILE = g++
CLEAN   = rm

# Main program
colour: colour.o
	$(COMPILE) $@.cc -o $@
#	$make clean #just to be mean

colour.o: colour.cc Graph.h Matrix.h Tuple.h defs.h LinkedList.h Node.h
	$(COMPILE) -c colour.cc

# Used for testing the graph and matrix classes
test: test.o
	$(COMPILE) $@.cc -o $@

test.o: test.cc Matrix.h Graph.h defs.h Tuple.h
	$(COMPILE) -c test.cc

#Remove all files produced
clean:
	$(CLEAN) --force colour *.o *~