COMPILE = g++
RM = rm

checkPi: checkPi.o
	$(COMPILE) checkPi.o -o $@

checkPi.o: checkPi.cc
	$(COMPILE) -c checkPi.cc	

randomNumber: randomNumber.o
	$(COMPILE) randomNumber.o -o $@

randomNumber.o: randomNumber.cc
	$(COMPILE) -c randomNumber.cc	
