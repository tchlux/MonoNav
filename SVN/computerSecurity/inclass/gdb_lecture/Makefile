GCC=g++ -g

all: first second third loop segfault segfault2

first: my_first_gdb.o
	$(GCC) -o first my_first_gdb.o

my_first_gdb.o:
	$(GCC) -c my_first_gdb.cc

second: my_second_gdb.o
	$(GCC) -o second my_second_gdb.o

my_second_gdb.o:
	$(GCC) -c my_second_gdb.cc

third: my_third_gdb.o
	$(GCC) -o third my_third_gdb.o

my_third_gdb.o:
	$(GCC) -c my_third_gdb.cc

loop: loop.o
	$(GCC) -o loop loop.o

loop.o:
	$(GCC) -c loop.cc

segfault: segfault.o
	$(GCC) -o segfault segfault.o

segfault.o:
	$(GCC) -c segfault.cc

segfault2: segfault2.o
	$(GCC) -o segfault2 segfault2.o

segfault2.o:
	$(GCC) -c segfault2.cc

clean:
	rm first second third loop segfault segfault2 *.o

tidy:
	rm *~


