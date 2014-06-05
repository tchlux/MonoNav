COMPILE = g++
clean = rm

testIntBinTree: testIntBinTree.o intBinTree.o intTreeNode.o
	$(COMPILE) testIntBinTree.o intBinTree.o intTreeNode.o -o $@

testIntBinTree.o: testIntBinTree.cc intBinTree.h intTreeNode.h
	$(COMPILE) -c testIntBinTree.cc

intBinTree.o: intBinTree.cc intBinTree.h intTreeNode.h
	$(COMPILE) -c intBinTree.cc

intTreeNode.o: intTreeNode.cc intTreeNode.h
	$(COMPILE) -c intTreeNode.cc

clean:
	$(CLEAN) testIntBinTree testIntBinTree.o intBinTree.o intTreeNode.o
