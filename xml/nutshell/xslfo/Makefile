cronbread.pdf: cronbread.fo
	fop -fo cronbread.fo -pdf cronbread.pdf

cronbread.fo : recipe.xml recipe.xsl
	xsltproc -o cronbread.fo recipe.xsl recipe.xml

.PHONY: clean
clean:
	rm -rf cronbread*
