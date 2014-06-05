GCC=g++

all: hack_passwords

hack_passwords: hack_passwords.o md5.o Read512.o RainbowTable.o
	$(GCC) -o hack_passwords hack_passwords.o md5.o Read512.o RainbowTable.o

hack_passwords.o: hack_passwords.cpp reductions.h RainbowTable.h custom_string_methods.h
	$(GCC) -c hack_passwords.cpp

RainbowTable.o: RainbowTable.cpp RainbowTable.h custom_string_methods.h 
	$(GCC) -c RainbowTable.cpp

md5.o: md5.cpp md5.h constants.h
	$(GCC) -c md5.cpp

Read512.o: Read512.cpp Read512.h constants.h
	$(GCC) -c Read512.cpp

clean:
	rm *.o ./hack_passwords

tidy:
	rm *~