from xml.sax.handler import ContentHandler
from xml.sax import parse

class TestHandler(ContentHandler):
    def startElement (self, name, attrs):
        print '=== start ==='
        print name, attrs.items()

    def characters (self, string):
        print '=== string ==='
        print string

    def endElement (self, name):
        print '=== end ==='
        print name

parse ('Elwin.xml', TestHandler())


