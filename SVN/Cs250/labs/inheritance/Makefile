COMPILE = g++
CLEAN = rm

phoneArray: phoneArray.o phone.o tt_phone.o
	$(COMPILE) $@.o phone.o tt_phone.o -o $@

phoneArray.o: phoneArray.cc
	$(COMPILE) -c phoneArray.cc

phone.o: phone.cc phone.h
	$(COMPILE) -c phone.cc

tt_phone.o: tt_phone.cc tt_phone.h
	$(COMPILE) -c tt_phone.cc