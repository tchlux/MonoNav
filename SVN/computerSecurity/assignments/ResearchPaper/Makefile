tex =  pdflatex
bib = bibtex
clean = rm -f
m = make

main: research.tex research.bib
	$(m) firstTex
	$(m) FinalBib
	$(m) secondTex
	$(m) finalPaper
	$(m) clean

finalPaper:
	$(tex) research

secondTex:
	$(tex) research

FinalBib:
	$(bib) research

firstTex:
	$(tex) research

clean:
	$(clean) research.bbl research.aux research.blg research.log research.dvi