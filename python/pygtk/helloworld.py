import pygtk
pygtk.require('2.0')
import gtk

class HelloWorld:
    def hello (slef, widget, data=None):
        print ("hello world")

    def delete_event (self, widget, event, data=None):
        print ("delete event occured")
        return False
    
    def destroy (self, widget, data=None):
        print ("and then destory event")
        gtk.main_quit()
    
    def __init__ (self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.connect ('delete_event', self.delete_event)
        self.window.connect ('destroy', self.destroy)
        self.window.set_border_width (10)
        self.window.set_position (gtk.WIN_POS_MOUSE)
        
        self.button = gtk.Button ("Hello World")
        self.button.connect ('clicked', self.hello, None)
# guess what this line will do? Destroy the button itself 
#        self.button.connect_object ('clicked', gtk.Widget.destroy, self.button)

#        self.button.connect_object ('clicked', gtk.Widget.destroy, self.window)


        self.window.add (self.button)
        
        self.window.show_all()

    def main (self):
        gtk.main()


if __name__ == '__main__':
    hello = HelloWorld ()
    hello.main()
