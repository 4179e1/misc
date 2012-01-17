import urllib2
h=urllib2.HTTPHandler (debuglevel=1)
request = urllib2.Request ('http://poetpalace.org/test.html')
request.add_header ('User-Agent', 'OpenANything/1.0 +http://diveintopython.org/')
opener = urllib2.build_opener(h)
feeddata = opener.open(request).read()
