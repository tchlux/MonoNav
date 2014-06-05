COMPILE = g++
RM = rm

eval: eval.o TokenArray.o Token.o String.o
	$(COMPILE) eval.o TokenArray.o Token.o String.o -o eval

eval.o: eval.cc TokenArray.h Token.h String.h
	$(COMPILE) -c eval.cc

TokenArray.o: TokenArray.cc TokenArray.h Token.h String.h
	$(COMPILE) -c TokenArray.cc

Token.o: Token.cc Token.h String.h
	$(COMPILE) -c Token.cc

String.o: String.cc
	$(COMPILE) -c String.cc

clean:
	$(RM) eval eval.o TokenArray.o Token.o String.o *~