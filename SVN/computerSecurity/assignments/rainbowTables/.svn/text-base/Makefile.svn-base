COMPILE=g++
CLEAN=rm
GET=get

build_rainbow: makeRainbowTable.o reductions.o md5.o Read512.o
	$(COMPILE) makeRainbowTable.o reductions.o md5.o Read512.o -o $@

makeRainbowTable.o: makeRainbowTable.cc reductions.h
	$(COMPILE) -c makeRainbowTable.cc

reductions.o: reductions.cpp reductions.h
	$(COMPILE) -c reductions.cpp

md5.o: md5.cpp md5.h Read512.h
	$(COMPILE) -c md5.cpp

Read512.o: Read512.cpp Read512.h
	$(COMPILE) -c Read512.cpp

clean:
	$(CLEAN) -f *.o build_rainbow