from xml.sax.handler import ContentHandler
from xml.sax import parse

class HeadlineHandler(ContentHandler):
    in_headline = False

    def __init__ (self, headlines):
        ContentHandler.__init__(self)
        self.headlines = headlines
        self.data=[]


    def startElement (self, name, attrs):
        if name == 'h1':
            self.in_headline = True

    def characters (self, string):
        if self.in_headline:
            self.data.append (string)

    def endElement (self, name):
        if name == 'h1':
            text = ''.join (self.data)
            self.data = []
            self.headlines.append(text)
            self.in_headline = False

headlines = []

parse ('website.xml', HeadlineHandler(headlines))
print 'The folloinwg <h1> elements were found:'
for h in headlines:
    print h

