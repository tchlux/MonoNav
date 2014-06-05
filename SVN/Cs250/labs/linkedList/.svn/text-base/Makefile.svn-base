COMPILE = g++
CLEAN = rm

useIntList: useIntList.o intList.o intNode.o
	$(COMPILE) useIntList.o intList.o intNode.o -o $@

useIntList.o: useIntList.cc intList.h intNode.h
	$(COMPILE) -c useIntList.cc

intList.o: intList.cc intList.h intNode.h
	$(COMPILE) -c intList.cc

intNode.o: intNode.cc intNode.h	
	$(COMPILE) -c intNode.cc

clean:
	$(CLEAN) useIntList useIntList.o intList.o intNode.o