dialog: dialog.xml
	cc dialog.c -o dialog -export-dynamic `pkg-config --libs --cflags gtk+-2.0 libglade-2.0`
dialog.xml: dialog.glade
	gtk-builder-convert dialog.glade dialog.xml
