COMPILE = g++
CLEAN   = rm -f

#list all directories required for compile
INCLUDES = -I /home/students/thlux/thlux/util/* tkLib/* tkLib/base/*

# All main programs to be build
MAIN = tkHelloWorld

# All .cc files with corresponding .h files
CCSWHS = tkLib/cpptk.cc

# All .h's without .cc's should be included on this line
HS = $(CCSWHS:.cc=.h) 

# All .o files required
OS = $(MAIN:.cc=.o) $(CCSWHS:.cc=.o)

# Make the main file
all:	$(MAIN)
	@echo $(SOURCES) are now compiled! :D

# Make the main with the .o's and .h's as dependencies
$(MAIN): $(OS) $(HS)
	$(COMPILE) $(OS) -o $@

# Make the .o's with the .cc's and .h's as dependencies
$(OS): $(CCSWHS) $(HS)
	$(COMPILE) $(INCLUDES) -c $(CCSWHS) $(MAIN).cc

# Clean up everything that was built
clean:
	$(CLEAN) $(OS) $(MAIN) *~
