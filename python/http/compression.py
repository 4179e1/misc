import urllib2
h = urllib2.HTTPHandler (debuglevel=1)
request = urllib2.Request ('http://poetpalace.org/compression.html')
request.add_header ("Accept-encoding", "gzip")
opener = urllib2.build_opener (h)
f = opener.open (request)
data = f.read()

if f.headers.get ('content-encoding', '') == 'gzip':
	import stringIO, gzip
	datastream = StringIO.StringIO (data)
	gzipper = gzip.GzipFile (fileobject=datastream)
	data = gzipper.read()

print data
