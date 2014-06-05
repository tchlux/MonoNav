COMPILE = g++
CLEAN = rm -f
ALL = cube cube2 Model sphere sphere2 texture triangle
CURR = texture
INCLUDE = -lGL -lglfw -lGLEW

curr: $(CURR)

all: $(ALL)

texture: texture.o
	$(COMPILE) $@.o -o $@ $(INCLUDE)

texture.o: texture.cc
	$(COMPILE) -c texture.cc


sphere2: sphere2.o Model.o
	$(COMPILE) sphere2.o Model.o -o $@ $(INCLUDE)

sphere2.o: sphere2.cc
	$(COMPILE) -c sphere2.cc

sphere: sphere.o sphere.cc
	$(COMPILE) sphere.o -o $@ $(INCLUDE)

sphere.o: sphere.cc
	$(COMPILE) -c sphere.cc


sphereTest: sphereTest.o sphereTest.cc
	$(COMPILE) sphereTest.o -o $@ $(INCLUDE)

sphereTest.o: sphereTest.cc
	$(COMPILE) -c sphereTest.cc

cube: cube.o cube.cc Model.o
	$(COMPILE) cube.o Model.o -o $@ $(INCLUDE)

cube.o: cube.cc
	$(COMPILE) -c cube.cc

cube2: cube2.o cube2.cc Model.o
	$(COMPILE) cube2.o Model.o -o $@ $(INCLUDE)

cube2.o: cube2.cc
	$(COMPILE) -c cube2.cc


Model.o: Model.cc Model.h
	$(COMPILE) -c Model.cc

triangle: triangle.o triangle.cc
	$(COMPILE) triangle.o -o $@ $(INCLUDE)

triangle.o: triangle.cc
	$(COMPILE) -c triangle.cc

clean:
	$(CLEAN) *~ *# *.o $(ALL)