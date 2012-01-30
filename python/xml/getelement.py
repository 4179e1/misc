from xml.dom import minidom
xmldoc = minidom.parse ('binary.xml')
reflist = xmldoc.getElementsByTagName ('ref')
print reflist
print reflist[0].toxml()
print reflist[1].toxml()

firstref = reflist[0]
print firstref.toxml()
plist = firstref.getElementsByTagName ('p')
print plist
print plist[0].toxml()
print plist[1].toxml()

plist = xmldoc.getElementsByTagName ('p')
print plist[0].toxml()
print plist[1].toxml()
print plist[2].toxml()

