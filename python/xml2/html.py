from xml.sax import parse
from xml.sax.handler import ContentHandler

class PageMaker(ContentHandler):
    passthrough = False
    def startElement (self, name, attrs):
        if name == 'page':
            self.passthrough = True
            self.out = open (attrs['name'] + '.html', 'w')
            self.out.write ('<html><head><title>%s</title></head><body>' % attrs['title'])
        elif self.passthrough:
            self.out.write ('<' + name )
            for key, val in attrs.items():
                self.out.write (' %s="%s"' % (key, val))
            self.out.write ('>')
        else: print 'Start what? %s' % name

    def endElement (self, name):
        if name == 'page':
            self.out.write ('</body></html>\n')
            self.out.close ()
            self.passthrough = False
        elif self.passthrough:
            self.out.write ('</%s>' % name)
        else: print 'End what? %s' % name

    def characters (self, chars):
        if self.passthrough: self.out.write (chars)
        else: print 'Char what? %s' % chars

parse ('website.xml', PageMaker())
