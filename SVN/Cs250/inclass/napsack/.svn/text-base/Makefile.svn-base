COMPILE = g++
CLEAN = rm

napsack: napsack.o
	$(COMPILE) napsack.cc -o $@

napsack.o: napsack.cc
	$(COMPILE) -c napsack.cc

clean:
	$(CLEAN) napsack napsack.o