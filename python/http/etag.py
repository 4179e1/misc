import urllib2, openanything
request = urllib2.Request ('http://poetpalace.org/test.html')
opener = urllib2.build_opener (openanything.DefaultErrorHandler())
firstdatastream = opener.open (request)
print firstdatastream.headers.get('ETag')
firstdata = firstdatastream.read()
print firstdata

request.add_header ('If-None-Match', firstdatastream.headers.get('ETag'))
seconddatastream = opener.open (request)
print seconddatastream.status
print seconddatastream.read()
