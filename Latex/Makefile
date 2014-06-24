COMPILE = pdflatex
CITE = bibtex
DOCUMENT = example
CLEAN = rm -f

all: example.tex example.bib
	$(COMPILE) example
	$(CITE) example
	$(COMPILE) example
	$(COMPILE) example
	$(CLEAN) *.aux *.bbl *.blg *.dvi *.log *# *~
	$ evince example.pdf
