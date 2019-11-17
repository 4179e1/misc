from xml.sax.handler import ContentHandler
from xml.sax import parse
import os

class Dispatcher:
    def dispatch (self, prefix, name, attrs=None):
        mname = prefix + name.capitalize()
        dname = 'default' + prefix.capitalize()
        method = getattr (self, mname, None)
        if callable (method): args = ()
        else:
            method = getattr (self, dname, None)
            args = name,
        print ' Desire: %15s Failback: %15s Got: %s' % (mname, dname, method)
        if prefix == 'start' : args += attrs,
        if callable (method): method (*args)

    def startElement (self, name, attrs):
        self.dispatch ('start', name, attrs)

    def endElement (self, name):
        self.dispatch ('end', name)

class WebsiteConstructor (Dispatcher, ContentHandler):
    passthrough = False
    def __init__ (self, directory):
        self.directory = [directory]
        self.ensureDirectory()

    def ensureDirectory(self): 
        path = os.path.join (*self.directory) 
        if not os.path.isdir (path): os.makedirs (path) 

    def characters (self, chars):
        if self.passthrough: self.out.write (chars)
        
    def defaultStart (self, name, attrs):
        if self.passthrough:
            self.out.write ('<' + name )
            for k,v in attrs.items():
                self.out.write (' %s="%s"' % (k, v))
            self.out.write ('>')

    def defaultEnd (self, name):
        if self.passthrough:
            self.out.write ('</%s>' % name)

    def startDirectory (self, attrs):
        self.directory.append (attrs['name'])
        self.ensureDirectory()
       
    def endDirectory (self):
        self.directory.pop()

    def startPage (self,attrs):
        filename = os.path.join (*(self.directory + [attrs['name']+'.html']))
        self.out = open (filename, 'w')
        self.writeHeader (attrs['title'])
        self.passthrough = True

    def endPage (self):
        self.writeFooter()
        self.out.close()
        self.passthrough = False

    def writeHeader (self, title):
        self.out.write ('<html><head><title>%s</title></head><body>' % title)

    def writeFooter (self):
        self.out.write ('</body></html>')

parse ('website.xml', WebsiteConstructor ('public_html'))
