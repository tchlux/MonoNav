COMPILE = g++ -O3
CLEAN = rm -f
UTIL = ~/thlux/util
GAME = $(UTIL)/Game
INCLUDES = -lGL -lglfw -lGLEW -lm -I $(UTIL)/Strops/ -I $(UTIL)/Matrix/ -I $(UTIL)/List/ -I ./
ALL = viewGL.o Clone.o Camera.o PlayerClone.o Model.o Material.o Vertex.o Shaders.o strops.o
RELY = constants.h Light.h $(UTIL)/List/List.h $(UTIL)/List/Link.h

Blocks: Blocks.o $(ALL) $(RELY)
	$(COMPILE) $@.o $(ALL) -o $@ $(INCLUDES)

test: test.o $(ALL) $(RELY)
	$(COMPILE) $@.o $(ALL) -o $@ $(INCLUDES)

#==================
#     .o files     
#==================

Blocks.o: Blocks.cc $(RELY) BlocksFunctions.cc
	$(COMPILE) -c Blocks.cc $(INCLUDES)

Camera.o: $(GAME)/Camera.cc $(GAME)/Camera.h $(RELY)
	$(COMPILE) -c $(GAME)/Camera.cc $(INCLUDES)

Clone.o: $(GAME)/Clone.cc $(GAME)/Clone.h $(RELY)
	$(COMPILE) -c $(GAME)/Clone.cc $(INCLUDES)

Gravity.o: Gravity.cc $(RELY)
	$(COMPILE) -c Gravity.cc $(INCLUDES)

Material.o: $(GAME)/Material.cc $(GAME)/Material.h $(RELY)
	$(COMPILE) -c $(GAME)/Material.cc $(INCLUDES)

Model.o: $(GAME)/Model.cc $(GAME)/Model.h $(RELY)
	$(COMPILE) -c $(GAME)/Model.cc $(INCLUDES)

PlayerClone.o: $(GAME)/PlayerClone.cc $(GAME)/PlayerClone.h $(RELY)
	$(COMPILE) -c $(GAME)/PlayerClone.cc $(INCLUDES)

Shaders.o: $(GAME)/Shaders.cc $(GAME)/Shaders.h $(RELY)
	$(COMPILE) -c $(GAME)/Shaders.cc $(INCLUDES)

strops.o: $(UTIL)/Strops/strops.h $(UTIL)/Strops/strops.cc $(RELY)
	$(COMPILE) -c $(UTIL)/Strops/strops.cc $(INCLUDES)

test.o: test.cc $(RELY)
	$(COMPILE) -c test.cc $(INCLUDES)

Vertex.o: $(GAME)/Vertex.cc $(GAME)/Vertex.h $(RELY)
	$(COMPILE) -c $(GAME)/Vertex.cc $(INCLUDES)

viewGL.o: $(GAME)/viewGL.cc $(GAME)/viewGL.h $(GAME)/Model.h $(RELY)
	$(COMPILE) -c $(GAME)/viewGL.cc $(INCLUDES)

#===================================
#     For removing excess files     
#===================================

clean:
	$(CLEAN) *.o test Blocks

