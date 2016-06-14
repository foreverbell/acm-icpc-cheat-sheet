all: main.tex
	xelatex main.tex
	xelatex main.tex

clean:
	rm -f *.log *.aux *.out *.pdf *.toc

.PHONY: clean
