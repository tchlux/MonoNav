COMPILE = g++
CLEAN   = rm -f
UTIL = ~/thlux/util
INCLUDES = -I $(UTIL)/Graph -I $(UTIL)/Tuple -I $(UTIL)/Loop -I $(UTIL)/Matrix -I $(UTIL)/List/
DEPENDS = $(UTIL)/List/Link.h
ALL = letterFreq connect station

station: station.o
	$(COMPILE) $@.o -o $@ $(INCLUDES)

station.o: station.cc  $(DEPENDS)
	$(COMPILE) -c station.cc $(INCLUDES)

connect: connect.o
	$(COMPILE) $@.o -o $@ $(INCLUDES)

connect.o: connect.cc
	$(COMPILE) -c connect.cc $(INCLUDES)

letterFreq: letterFreq.o
	$(COMPILE) letterFreq.o -o $@

letterFreq.o: letterFreq.cc
	$(COMPILE) $(INCLUDES) -c letterFreq.cc

# Clean up everything that was built
clean:
	$(CLEAN) *~ *.o $(ALL)
