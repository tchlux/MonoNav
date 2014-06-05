JC = javac
JRT = java
PWD = $(shell pwd)
INCLUDES = $(PWD)/lib/jogl/jar/gluegen-rt.jar:$(PWD)/lib/jogl/jar/jogl-all.jar:$(PWD)/lib/vecmath.jar
CFLAGS = -d bin -cp $(INCLUDES):$(PWD)/lib/*
PACKAGE_DIR = edu/roanoke/manualsegmentation
RTFLAGS = -cp $(INCLUDES):$(PWD)/bin
PACKAGE_NAME = edu.roanoke.manualsegmentation
MAIN = ManualSegmentation

.PHONY: check-syntax

check-syntax:
	javac -Xlint $(CHK_SOURCES)

all:
	$(JC) $(CFLAGS) src/$(PACKAGE_DIR)/*.java

run:
	java $(RTFLAGS) $(PACKAGE_NAME).$(MAIN)

clean:
	find bin -type f -name *.class -print0 | xargs -0 rm
