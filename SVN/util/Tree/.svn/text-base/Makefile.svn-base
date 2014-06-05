COMPILE = g++
CLEAN = rm 
TREE = ~/thlux/Cs250/labs/avlTrees
INCLUDES = -I $(TREE)/

testAVL: testAVL.o
	$(COMPILE) $@.o -o $@

testAVL.o: testAVL.cc $(TREE)/AVLnode.h $(TREE)/AVLTree.h AVL.h
	$(COMPILE) -c testAVL.cc $(INCLUDES)

clean:
	$(CLEAN) testAVL *.o