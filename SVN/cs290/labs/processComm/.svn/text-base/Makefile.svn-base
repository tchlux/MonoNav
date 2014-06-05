COMPILE = g++
CLEAN = rm -f
ALL = sleeper sleeper1 procreate procreateWait sybil comm commNB
EXE = comm

all: $(ALL)#$(EXE)

commNB: commNonBlocking.o
	$(COMPILE) commNonBlocking.o -o $@

commNonBlocking.o: commNonBlocking.cc
	$(COMPILE) -c commNonBlocking.cc

comm: comm.o
	$(COMPILE) comm.o -o $@

comm.o: comm.cc
	$(COMPILE) -c comm.cc

sybil: sybil.o
	$(COMPILE) sybil.o -o $@

sybil.o: sybil.cc
	$(COMPILE) -c sybil.cc

procreateWait: procreateWait.o
	$(COMPILE) procreateWait.o -o $@

procreateWait.o: procreateWait.cc
	$(COMPILE) -c procreateWait.cc

procreate: procreate.o
	$(COMPILE) procreate.o -o $@

procreate.o: procreate.cc
	$(COMPILE) -c procreate.cc

sleeper1: sleeper1.o
	$(COMPILE) sleeper1.o -o $@

sleeper1.o: sleeper1.cc
	$(COMPILE) -c sleeper1.cc

sleeper: sleeper.o
	$(COMPILE) sleeper.o -o $@

sleeper.o: sleeper.cc
	$(COMPILE) -c sleeper.cc

clean:
	$(CLEAN) *.o *~ *# $(ALL)