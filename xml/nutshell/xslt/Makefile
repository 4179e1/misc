XSL = $(shell ls *.xsl)
XML = $(XSL:%.xsl=%.xml)

all:
	for i in $(XSL); do xsltproc -o $${i%.xsl}.xml $$i person.xml;done

.PHONY: clean
clean:
	rm -rf $(XML)
