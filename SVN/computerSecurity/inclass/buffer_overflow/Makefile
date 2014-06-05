GCC=g++ -fno-stack-protector -g
CC=gcc -fno-stack-protector 

EXES=auth auth2 memory note note_exploit

all: $(EXES)

note: note_search.cc
	$(CC) -o $@ $(^)

note_exploit: note_exploit.cc
	$(CC) -o $@ $(^)

auth: user_auth.o
	$(GCC) -o $@ $(^)

user_auth.o: user_auth.cc
	$(GCC) -c $(^)

auth2: user_auth_2.o
	$(GCC) -o $@ $(^)

user_auth_2.o: user_auth_2.cc
	$(GCC) -c $(^)

memory: memory_examination.o
	$(GCC) -o $@ $(^)

memory_examination.o: memory_examination.cc
	$(GCC) -c $(^)

clean:
	rm *.o $(EXES)

tidy:
	-rm *~