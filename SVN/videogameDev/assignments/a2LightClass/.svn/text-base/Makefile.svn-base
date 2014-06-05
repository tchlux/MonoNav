COMPILE = g++
CLEAN = rm -f
UTIL = ~/thlux/util
GAME = $(UTIL)/Game
GAME_O = viewGL.o Model.o Material.o strops.o
INCLUDES = -lGL -lglfw -lGLEW -lm -I $(UTIL)/Strops/ -I $(GAME)/
ALL = cube testModel

current: testModel

all: $(ALL)	

#==========================
#     executable files     
#==========================

cube: cube.o
	$(COMPILE) $@.o -o $@ $(INCLUDES)

testModel: testModel.o $(GAME_O)
	$(COMPILE) $@.o $(GAME_O) -o $@ $(INCLUDES)
	$(CLEAN) *.o

#==================
#     .o files     
#==================

$(GAME_O):
	$ make -f $(GAME)/Makefile

testModel.o: testModel.cc
	$(COMPILE) -c testModel.cc $(INCLUDES)

#===================
#     Utilities     
#===================

clean:
	$(CLEAN) $(ALL) *.o *~ *#
