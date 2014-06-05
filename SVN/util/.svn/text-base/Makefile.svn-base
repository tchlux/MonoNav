COMPILE = g++
CLEAN   = rm -f

#list all directories required for compile
#INCLUDES = -I /home/students/thlux/thlux/util/*
INCLUDES = -I /home/thomas/thlux/util/*

# All main programs to be build
MAIN = 

# All .cc files with corresponding .h files
CCSWHS = 

# All .h's without .cc's should be included on this line
HS = $(CCSWHS:.cc=.h) 

# All .o files required
OS = $(MAIN).o $(CCSWHS:.cc=.o)

# Make the main file
all:	$(MAIN)
	@echo $(SOURCES) are now compiled! :D

# Make the main with the .o's and .h's as dependencies
$(MAIN): $(OS) $(HS)
	$(COMPILE) $(OS) -o $@

# Make the .o's with the .cc's and .h's as dependencies
$(OS): $(MAIN).cc $(CCSWHS) $(HS)
	$(COMPILE) $(INCLUDES) -c $(CCSWHS) $(MAIN).cc

# Clean up everything that was built
clean:
	$(CLEAN) $(OS) $(MAIN) *~
