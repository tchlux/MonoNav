COMPILE		= g++
CV_INCLUDE	= -I /usr/local/include/opencv/
CV_LINKS	= -l opencv_highgui -l opencv_ml

first: firstProgram.o
	$(COMPILE) $(CV_LINKS) firstProgram.o -o $@

firstProgram.o: firstProgram.cc
	$(COMPILE) $(CV_INCLUDE) -c firstProgram.cc 
