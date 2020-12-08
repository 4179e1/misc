all:
	@echo "usage: make {reset | clean | diff | patch}"

reset:
	cp -R ../originaldirectory ../updateddirectory . 

diff:
	-diff -u originaldirectory ../updateddirectory >patch.patch

patch:
	@-rm -rf updateddirectory
	patch -p0 -i patch.patch

reverse:
	@-rm -rf originaldirectory
	patch -p0 -R -i patch.patch

.PHONY: clean
clean:
	rm -rf originaldirectory updateddirectory patch.patch
