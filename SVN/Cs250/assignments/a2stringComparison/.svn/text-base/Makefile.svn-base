COMPILE = g++
RM = rm

stringMatch: String.o List.o FileReader.o helper.o stringMatch.o
	$(COMPILE) String.o List.o FileReader.o helper.o stringMatch.o -o stringMatch

stringMatch.o: String.cc String.h List.cc List.h FileReader.cc FileReader.h helper.cc helper.h stringMatch.cc
	$(COMPILE) -c stringMatch.cc

helper.o: helper.cc helper.h List.cc List.h String.cc String.h FileReader.cc FileReader.h
	$(COMPILE) -c helper.cc

FileReader.o: FileReader.cc FileReader.h String.cc String.h
	$(COMPILE) -c FileReader.cc

List.o: List.cc List.h
	$(COMPILE) -c List.cc

String.o: String.cc String.h
	$(COMPILE) -c String.cc

clean:
	$(RM) stringMatch *.o