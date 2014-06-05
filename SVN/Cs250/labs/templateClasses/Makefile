COMPILE = g++
REMOVE = rm

pairTest: pairTest.o
	$(COMPILE) pairTest.o -o $@

pairTest.o: pairTest.cc Pair.h
	$(COMPILE) -c pairTest.cc

stackTest: stackTest.o
	$(COMPILE) stackTest.o -o $@

stackTest.o: stackTest.cc Stack.h
	$(COMPILE) -c stackTest.cc

clean:
	$(REMOVE) pairTest pairTest.o stackTest stackTest.o
