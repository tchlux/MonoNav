COMPILE = g++
REMOVE = rm


md5encrypt:  MD5encrypt.o md5Hash.o Read512.o String.o
	$(COMPILE) MD5encrypt.o md5Hash.o Read512.o String.o -o $@

Md5encrypt.o: MD5encrypt.cc md5Hash.h
	$(COMPILE) -c MD5encrypt.cc

md5Hash.o: md5Hash.cc md5Hash.h Read512.h constants.h String.h
	$(COMPILE) -c md5Hash.cc

Read512.o: Read512.cpp Read512.h constants.h
	$(COMPILE) -c Read512.cpp

String.o: String.cc String.h
	$(COMPILE) -c String.cc

clean:
	$(REMOVE) md5encrypt *.o