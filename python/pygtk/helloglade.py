import sys
import pygtk
pygtk.require('2.0')
import gtk
import gtk.glade

class HelloGlade:
    def _do_run_dialog (self, dialog):
        dialog.show()
        response = dialog.run()
        dialog.hide()
        return response

    def _do_open (self):
            self._set_status (self.filename.split('/')[-1])
            self.file = open (self.filename, 'a+')

    def _do_save (self):
            start,end = self.textbuffer.get_bounds()
            text = self.textbuffer.get_text(start, end)
            self.file.truncate(0)
            self.file.write (text)

    def on_close_clicked (self, widget, data=None):
        response = self._do_run_dialog (self.cs)
        if response == gtk.RESPONSE_OK:
            if self.file is None:
                sr = self._do_run_dialog (self.fs)
                if sr == gtk.RESPONSE_OK:
                    self.filename = self.fs.get_filename()
                    self._do_open()
                else:
                    return
            self._do_save()
            self.file.close()
            self._reset()

    def on_save_clicked (self, widget, data=None):
        if self.file is None:
            response = self._do_run_dialog (self.fs)
            if response == gtk.RESPONSE_OK:
                self.filename = self.fs.get_filename()
                self._do_open()
                self._do_save()
        else :
            self._do_save()

    def open_clicked (self, widget, data=None):
        # there's a warning after setting reponse id in glade
        response = self._do_run_dialog (self.fc)
        if response == gtk.RESPONSE_OK:
            self.filename = self.fc.get_filename()
            self._do_open()
            self.textbuffer.set_text (self.file.read())

    def window_destroy (self, gobject, data=None):
        self.on_save_clicked (None, None)
        if self.file is not None:
            self.file.close()
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
        self.file = None
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
        self.cs = self.builder.get_object ('closesave')
        self.tv = self.builder.get_object ('textview')
        self.textbuffer = self.tv.get_buffer()

        self._reset()
        self.window.show()

if __name__ == '__main__':
    helloglade = HelloGlade()
    gtk.main()
