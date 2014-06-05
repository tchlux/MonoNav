COMPILE = g++
CLEAN   = rm
GET     = get

#list all directories required for compile
INCLUDES = -I/home/students/thlux/thlux/cs250/util/

#Name of an executable to be made
MAIN    = huffmanEncode
#All .cc files
SOURCES = huffmanEncode.cc File.cc String.cc icTuple.cc
OBJECTS = $(SOURCES:.cc=.o)
#^^ all the sources with .o's replacing .cc's


#All executables to be produced
all:	$(MAIN)
	@echo $(SOURCES) are now compiled! :D

#The main file, with all objects as dependencies
$(MAIN): $(OBJECTS)
	$(COMPILE) $(OBJECTS) -o $@

#Compiles all .o's given all sources and their .h counterparts
$(OBJECTS): $(SOURCES) $(SOURCES:.cc=.h)
	$(COMPILE) $(INCLUDES) -c  $(SOURCES)

refresh:
	$ make clean
	$ make clean_util
	$ make get_util

clean:
	$(CLEAN) huffmanEncode testAll *.o *~ *.puff *.huff

clean_util:
	$(CLEAN) String.* File.* Tuple.h icTuple.* Tree.h treeNode.h huffmanTree.* LinkedList.h Node.h

get_util:
	$(GET) String/*
	$(GET) Tuple/*
	$(GET) Tree/*
	$(GET) LinkedList/*
	$(GET) File/*









# #Remove all files produced
# clean:
# 	$(CLEAN) $(OBJECTS) $(MAIN) *~

# COMPILE = g++
# CLEAN = rm

# huffmanEncode: huffmanEncode.o File.o String.o icTuple.o
# 	$(COMPILE) huffmanEncode.o File.o String.o icTuple.o -o $@

# testAll: testAll.o huffmanEncode.o File.o String.o icTuple.o
# 	$(COMPILE) testAll.o huffmanEncode.o File.o String.o icTuple.o -o $@

# testAll.o: testAll.cc File.h String.h icTuple.h LinkedList.h Node.h Tree.h treeNode.h
# 	$(COMPILE) -c testAll.cc

# huffmanEncode.o: huffmanEncode.cc File.h String.h icTuple.h LinkedList.h Node.h Tree.h treeNode.h
# 	$(COMPILE) -c huffmanEncode.cc

# File.o: File.cc File.h String.h
# 	$(COMPILE) -c File.cc

# String.o: String.cc String.h
# 	$(COMPILE) -c String.cc

# icTuple.o: icTuple.cc icTuple.h
# 	$(COMPILE) -c icTuple.cc
