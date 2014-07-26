COMPILE = pdflatex
CITE = bibtex
DOCUMENT = lux2014tetramedian
CLEAN = rm -f

all: $(DOCUMENT).tex $(DOCUMENT).bib
	$(COMPILE) $(DOCUMENT)
	$(CITE) $(DOCUMENT)
	$(COMPILE) $(DOCUMENT)
	$(COMPILE) $(DOCUMENT)
	$(CLEAN) *.aux *.bbl *.blg *.dvi *.log *# *~
	$ evince $(DOCUMENT).pdf
