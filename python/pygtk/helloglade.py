import sys
import pygtk
pygtk.require('2.0')
import gtk
import gtk.glade

class HelloGlade:
    def on_close_clicked (self, widget, data=None):
        pass
        
    def on_filesave_response (self, widget, signal, data=None):
        print (signal)
        # TODO
        pass

    def on_save_clicked (self, widget, data=None):
        if self.filename is None:
            self.fs.show()
            self.fs.run()
            self.fs.hide()
        else :
            print ('saving file')
            start,end = self.textbuffer.get_bounds()
            text = self.textbuffer.get_text(start, end)
            self.file.truncate(0)
            self.file.write (text)
            self.file.close()

    def on_fc_response (self, widget, response, data=None):
        if response == gtk.RESPONSE_OK:
            self.filename = self.fc.get_filename()
            self._set_status (self.filename.split('/')[-1])

            self.file = open (self.filename, 'rw+')
            self.textbuffer.set_text (self.file.read())

    def open_clicked (self, widget, data=None):
        # there's a warning after setting reponse id in glade
        self.fc.show()
        response = self.fc.run()
        self.fc.hide()

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

    def _reset (self):
        self._set_status ('untitiled')
        self.filename = None
        self.textbuffer.set_text('')
        

    def __init__ (self):
        self.gladefile = 'helloglade.xml'
        self.builder = gtk.Builder()
        self.builder.add_from_file (self.gladefile)
        self.builder.connect_signals(self)

        self.window = self.builder.get_object ('window')
        self.sb = self.builder.get_object ('statusbar')
        self.sbid = self.sb.get_context_id ('untitiled')
        self.fc = self.builder.get_object ('filechooserdialog')
        self.fs = self.builder.get_object ('filesave')
        self.tv = self.builder.get_object ('textview')
        self.textbuffer = self.tv.get_buffer()

        self._reset()
        self.window.show()


if __name__ == '__main__':
    helloglade = HelloGlade()
    gtk.main()
