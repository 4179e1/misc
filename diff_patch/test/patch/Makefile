all:
	@echo "usage: make {reset | diff | patch | diffc | patchc | diffu | patchu}"

reset:
	cp ../origin ../updated .

diff:
	-diff origin updated >patch.patch

patch:
	patch origin -i patch.patch -o updated

diffc:
	-diff -c origin updated >patchc.patch

patchc:
	patch -i patchc.patch -o updatedc
	
diffu:
	-diff -u origin updated >patchu.patch
	
patchu:
	patch -i patchu.patch -o updateu


.PHONY: clean
clean:
	rm -rf origin updated updatedc updatedu patch.patch patchc.patch patchu.patch
