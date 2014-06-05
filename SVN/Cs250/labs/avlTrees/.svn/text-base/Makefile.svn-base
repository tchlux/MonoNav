COMPILE = g++
CLEAN = rm

testavl: AVLMain.o
	$(COMPILE) AVLMain.cc -o $@

AVLMain.o: AVLMain.cc AVLnode.h AVLTree.h
	$(COMPILE) -c AVLMain.cc

clean:
	$(CLEAN) testavl AVLMain.o