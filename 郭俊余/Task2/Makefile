all: impress.pdf

impress.pdf: impress.md
	pandoc -t beamer --pdf-engine=xelatex --template=template.tex $^ -V CJKmainfont='Noto Sans CJK SC' -V indent --slide-level=2 -o $@

clean:
	rm impress.pdf
