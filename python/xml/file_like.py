from xml.dom import minidom
fsock = open ('binary.xml')
xmldoc = minidom.parse (fsock)
fsock.close()
print xmldoc.toxml()

# import urllib
# usock = urllib.urlopen ("http://slashdot.org/slashdot.rdf")
# xmldoc = minidom.parse (usock)
# usock.close()
# print xmldoc.toxml()

contents = "<grammar><ref id='bit'><p>0</p><p>1</p></ref></grammar>"
xmldoc = minidom.parseString(contents)
print xmldoc.toxml()

contents = "<grammar><ref id='bit'><p>0</p><p>1</p></ref></grammar>"
import StringIO
ssock = StringIO.StringIO(contents)
print ssock.read()
#empty
print ssock.read()

ssock.seek(0)
print ssock.read(15)
#the rest of stream
print ssock.read()
#empty
print ssock.read()
ssock.close()

contents = "<grammar><ref id='bit'><p>0</p><p>1</p></ref></grammar>"
ssock = StringIO.StringIO (contents)
xmldoc = minidom.parse (ssock)
ssock.close()
print xmldoc.toxml()
