tex =  pdflatex
bib = bibtex
clean = rm -f
m = make
COMPILE = g++
# Preparing the whole shebang
main: answers.tex prob2partd.cc prob5parta.cc prob7parta.cc
	$(m) finalPaper
	$(m) prob2partd
	$(m) prob5parta
	$(m) prob7parta
	$(m) clean

# Paper answers code
finalPaper:
	$(tex) answers

# Problem 2 Code
prob2partd: prob2partd.o
	$(COMPILE) $@.o -o $@

prob2partd.o: prob2partd.cc
	$(COMPILE) -c prob2partd.cc

# Problem 5 Code
prob5parta: prob5parta.o
	$(COMPILE) $@.o -o $@

prob5parta.o: prob5parta.cc
	$(COMPILE) -c prob5parta.cc

# Problem 7 Code
prob7parta: prob7parta.o
	$(COMPILE) $@.o -o $@

prob7parta.o: prob7parta.cc
	$(COMPILE) -c prob7parta.cc

# Clean it all up
clean:
	$(clean) answers.dvi answers.log answers.aux *.o *~

pclean:
	$(clean) prob2partd prob5parta prob7parta