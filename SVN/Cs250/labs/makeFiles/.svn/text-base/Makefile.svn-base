GCC = g++
RM = rm

rundate: date.o testDate.o
	$(GCC)  testDate.o date.o -o rundate

testDate.o: testDate.cc date.h
	$(GCC)  -c testDate.cc

date.o: date.cc date.h
	$(GCC)	-c date.cc

clean: 
	$(RM) date.o testDate.o rundate


