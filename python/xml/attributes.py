from xml.dom import minidom
xmldoc = minidom.parse ('binary.xml')
reflist = xmldoc.getElementsByTagName ('ref')
bitref = reflist[0]
print bitref.toxml()
print bitref.attributes
print bitref.attributes.keys()
print bitref.attributes.values()
print bitref.attributes["id"]

a = bitref.attributes["id"]
print a
print a.name
print a.value
