GCC = g++
MOVE = mv

# test: LC2200
# 	./LC2200 < test1.txt
# 	./LC2200 < test2.txt
# 	./LC2200 < test3.txt

Choice.o: Choice.cc Choice.h constants.h
	$(GCC) -c Choice.cc

CPU.o: CPU.cc CPU.h utilities.h
	$(GCC) -c CPU.cc

Machine.o: Machine.cc Machine.h CPU.h Memory.h utilities.h constants.h
	$(GCC) -c Machine.cc

Memory.o: Memory.cc Memory.h utilities.h constants.h
	$(GCC) -c Memory.cc

Simulator.o: Simulator.cc Machine.h constants.h Choice.h
	$(GCC) -c Simulator.cc

testMem: testMem.o Memory.o utilities.o
	$(GCC) -o testMem testMem.o Memory.o utilities.o

testMem.o: testMem.cc Memory.h
	$(GCC) -c testMem.cc

testMachine: testMachine.o Memory.o CPU.o utilities.o Machine.o
	$(GCC) -o tM testMachine.o Memory.o CPU.o utilities.o Machine.o

testMachine.o: testMachine.cc Machine.h
	$(GCC) -c testMachine.cc

utilities.o: utilities.cc utilities.h constants.h
	$(GCC) -c utilities.cc

LC2200: Simulator.o Machine.o CPU.o Memory.o utilities.o Choice.o 
	$(GCC) -o $@ Simulator.o Machine.o CPU.o Memory.o utilities.o Choice.o 
	# $(MOVE) $@ ./simTestFiles/
	# echo "Moved the output to simTestFiles"

clean: 
	rm -f *.o *~ LC2200 testMachine testMem callback