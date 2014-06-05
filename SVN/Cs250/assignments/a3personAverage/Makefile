COMPILE = g++
REMOVE = rm

personAverage: personAverage.o peopleHelper.o People.o Person.o String.o mymath.o
	$(COMPILE) personAverage.o peopleHelper.o People.o Person.o String.o mymath.o -o $@

personAverage.o: personAverage.cc peopleHelper.h People.h Person.h String.h mymath.h
	$(COMPILE) -c personAverage.cc

peopleHelper.o: peopleHelper.cc peopleHelper.h People.h Person.h String.h mymath.h
	$(COMPILE) -c peopleHelper.cc

People.o: People.cc People.h Person.h
	$(COMPILE) -c People.cc

Person.o: Person.cc Person.h String.h
	$(COMPILE) -c Person.cc

String.o: String.cc String.h
	$(COMPILE) -c String.cc

mymath.o: mymath.cc mymath.h
	$(COMPILE) -c mymath.cc

clean:
	$(REMOVE) personAverage personAverage.o peopleHelper.o People.o Person.o String.o mymath.o