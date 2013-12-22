import sys
import pygtk
pygtk.require('2.0')
import gtk
import gtk.glade

class HelloGlade:
    def window_destroy (self, gobject, data=None):
        gtk.main_quit()

    def about_activate (self, widget, data=None):
        print ('self', self)
        print ('widget', widget)
        print ('data', data)
        widget.show()

    def about_delete_event (self, widget, event, data=None):
        print ('delete_event signal', data)
        print ('self', self)
        print ('widget', widget)
        print ('event', event)
        print ('data', data)
        widget.hide()
        return True

    def __init__ (self):
        self.gladefile = 'helloglade.xml'
        self.builder = gtk.Builder()
        self.builder.add_from_file (self.gladefile)
        self.builder.connect_signals(self)
        self.window = self.builder.get_object ('window')
        self.window.show()


if __name__ == '__main__':
    helloglade = HelloGlade()
    gtk.main()
