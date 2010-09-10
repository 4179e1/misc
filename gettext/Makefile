TAR=fool

genpo:
	rm zh_CN.po
	xgettext -a $(TAR).c -o fool.pot
	msginit -l zh_CN.utf8 -i fool.pot

genmo:
	msgfmt zh_CN.po -o zh_CN.mo
