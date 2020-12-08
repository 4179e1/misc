"""Miscellaneous utility functions"""

def openAnything (source):
	"""URI, filename, or string --> stream

	This function lest you define parsers that take any input soure
	(URL, pathname to local or network file, or actual data as a string)
	and deal with it in a uniform manner. Returned object is guaranteed
	to have all the basice stdio read methods (read, readline, redlines)
	Just .close () the object when your're done with it.

	Examples:
	>>> form xml.dom import minidom
	>>> sock = openAnything ("http://localhost/kant.xml")
	>>> doc = minidom.parse (sock)
	>>> sock.close()
	>>> sock = openAnything ("/home/lyre/misc/python/xml/kant.xml")
	>>> doc = minidom.parse(sock)
	>>> sock.close()
	>>> sock = openAnything ("<ref id='conjunction'><<text>and</text><text><or></text></ref>")
	>>> doc = minidom.parse (sock)
	>>> sock.close()
	"""
	if (hasattr (source, "read")):
		return source

	if source == '-':
		import sys
		return sys.stdin

	# try to open with urllib (if source is http, ftp, orf file URL)
	import urllib
	try:
		return urllib.urlopen(source)
	except (IOError, OSError):
		pass
	
	# try to open with native open function (if source is pathname)
	try:
		return open(source)
	except (IOError, OSError):
		pass

	#treat source as string
	import StringIO
	return StringIO.StringIO (str(source))
		
