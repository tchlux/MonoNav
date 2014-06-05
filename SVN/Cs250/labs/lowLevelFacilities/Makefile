COMPILE = g++
CLEAN = rm

typeSizes: typeSizes.o String.o
	$(COMPILE) typeSizes.o String.o -o $@

typeSizes.o: typeSizes.cc String.h
	$(COMPILE) -c typeSizes.cc

String.o: String.cc String.h
	$(COMPILE) -c String.cc

bitsAndBytes: bitsAndBytes.o
	$(COMPILE) bitsAndBytes.o -o bitsAndBytes

bitsAndBytes.o: bitsAndBytes.cc
	$(COMPILE) -c bitsAndBytes.cc

masking: masking.o
	$(COMPILE) masking.o -o masking

masking.o: masking.cc
	$(COMPILE) -c masking.cc

clean:
	$(CLEAN) String.o typeSizes.o typeSizes
	$(CLEAN) bitsAndBytes.o bitsAndBytes
	$(CLEAN) masking.o masking