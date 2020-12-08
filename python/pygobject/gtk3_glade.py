from gi.repository import Gtk

class MyWindow():
    def __init__ (self):
        self.builder = Gtk.Builder()
        self.builder.add_from_file ('gtk3_glade.glade')
        self.builder.connect_signals (self)
        self.window = self.builder.get_object('window')
        self.window.show_all()

    def on_hello_clicked (self, widget, data=None):
        print ("hello")

    def on_window_destroy (self, widget, data=None):
        Gtk.main_quit()

win = MyWindow()
Gtk.main()
