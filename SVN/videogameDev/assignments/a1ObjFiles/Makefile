COMPILE = g++
CLEAN = rm -f
INCLUDES = -lGL -lglfw -lGLEW -lm
ALL = cube Model sphere2 testModel viewGL 

current: testModel

all: $(ALL)

#==========================
#     executable files     
#==========================

%: %.o
	$(COMIPLE) %.o -o $@ $(INCLUDES)

cube: cube.o
	$(COMPILE) $@.o -o $@ $(INCLUDES)

Model: Model.o
	$(COMPILE) $@.o -o $@ $(INCLUDES)

sphere2: sphere2.o Model.o
	$(COMPILE) sphere2.o Model.o -o $@ $(INCLUDES)

testModel: testModel.o Model.o viewGL.o
	$(COMPILE) $@.o Model.o viewGL.o -o $@ $(INCLUDES)

viewGL: viewGL.o
	$(COMPILE) $@.o -o $@ $(INCLUDES)

#==================
#     .o files     
#==================

cube.o: cube.cc
	$(COMPILE) -c cube.cc

Model.o: Model.cc Model.h
	$(COMPILE) -c Model.cc

sphere2.o: sphere2.cc
	$(COMPILE) -c sphere2.cc

testModel.o: testModel.cc Model.h strops.h
	$(COMPILE) -c testModel.cc

viewGL.o: viewGL.cc viewGL.h Model.h
	$(COMPILE) -c viewGL.cc

%.o: %.cc
	$(COMPILE) -c %.cc

#===================
#     Utilities     
#===================

clean:
	$(CLEAN) $(ALL) *.o *~ *#