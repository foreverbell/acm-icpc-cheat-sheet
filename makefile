all: template.tex
	xelatex template.tex
	xelatex template.tex

clean:
	rm -f *.log *.aux *.out *.pdf *.toc

.PHONY: clean