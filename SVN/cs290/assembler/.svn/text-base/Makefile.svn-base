COMPILE = g++
UTIL = ~/thlux/util
INCLUDES = -I $(UTIL)/LinkedList/ -I $(UTIL)/Strops/
ALL = assemble
CLEAN = rm -f
TAR = tar -czf

assemble: assemble.o 
	$(COMPILE) $@.o -o $@

assemble.o: assemble.cc assemble.h syntaxCheck.h
	$(COMPILE) -c assemble.cc $(INCLUDES)

clean:
	$(CLEAN) *.o *~ *# $(ALL)

tar:
	$(TAR) thlux_290_assembler.tgz ./*