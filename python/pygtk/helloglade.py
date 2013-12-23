import sys
import pygtk
pygtk.require('2.0')
import gtk
import gtk.glade

class HelloGlade:
    def open_clicked (self, widget, data=None):
        self.fc.show()
    def on_file_activated (self, widget, data=None):
        self.filename = self.fc.get_filename()
        self._set_status (self.filename.split('/')[-1])

        self.fc.hide()
        self.file = open (self.filename, 'rw')
        textbuffer = self.tv.get_buffer()
        textbuffer.set_text (self.file.read())


    def window_destroy (self, gobject, data=None):
        gtk.main_quit()

    def about_activate (self, widget, data=None):
        widget.show()

    def hide_on_delete_event (self, widget, event, data=None):
        widget.hide()
        return True
    def _set_status (self, text):
        self.sb.pop (self.sbid)
        self.sb.push (self.sbid, text)

    def __init__ (self):
        self.filename = None
        self.gladefile = 'helloglade.xml'
        self.builder = gtk.Builder()
        self.builder.add_from_file (self.gladefile)
        self.builder.connect_signals(self)

        self.window = self.builder.get_object ('window')
        self.sb = self.builder.get_object ('statusbar')
        self.sbid = self.sb.get_context_id ('untitiled')
        self._set_status ('untitiled')
        self.window.show()

        self.fc = self.builder.get_object ('filechooserdialog')
        self.tv = self.builder.get_object ('textbuffer')

if __name__ == '__main__':
    helloglade = HelloGlade()
    gtk.main()
