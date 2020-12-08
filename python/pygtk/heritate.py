import pygtk
pygtk.require('2.0')
import gtk

class MyWin (gtk.Window):
    def __init__ (self):
        gtk.Window.__init__ (self)

mw = MyWin()
mw.connect("destroy", gtk.main_quit)
mw.show_all()
gtk.main()
