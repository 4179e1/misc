import urllib2, openanything
h=urllib2.HTTPHandler (debuglevel=1)
request = urllib2.Request ('http://poetpalace.org/redirect.html')
opener = urllib2.build_opener(h, openanything.SmartRedirectHandler())
f = opener.open(request)
print f.status

