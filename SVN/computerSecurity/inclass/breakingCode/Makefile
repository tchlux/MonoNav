COMPILE = g++
CLEAN = rm

find_passwords: find_match.o FileReader.o
	$(COMPILE) find_match.o FileReader.o String.o -o $@

find_match.o: find_match.cc
	$(COMPILE) -c find_match.cc

gen_file: generate_encryptions.o md5.o Read512.o FileReader.o String.o
	$(COMPILE) generate_encryptions.o md5.o Read512.o FileReader.o String.o -o $@

generate_encryptions.o: generate_encryptions.cc md5.h Read512.h FileReader.h String.h
	$(COMPILE) -c generate_encryptions.cc

md5.o: md5.cpp md5.h Read512.h
	$(COMPILE) -c md5.cpp

Read512.o: Read512.cpp Read512.h
	$(COMPILE) -c Read512.cpp

FileReader.o: FileReader.cc FileReader.h String.h
	$(COMPILE) -c FileReader.cc

String.o: String.cc String.h
	$(COMPILE) -c String.cc

clean: 
	$(CLEAN) generate_encryptions.o md5.o Read512.o FileReader.o String.o gen_file