import urllib2
h=urllib2.HTTPHandler (debuglevel=1)
request = urllib2.Request ('http://poetpalace.org/test.html')
opener = urllib2.build_opener(h)
firstdatastream = opener.open(request)
print firstdatastream.headers.dict

print firstdatastream.headers.get('Last-Modified')
request.add_header ('If-Modified-Since', firstdatastream.headers.get('Last-Modified'))

#except:

#seconddatastream = opener.open(request)
import openanything
#set up handler
opener = urllib2.build_opener(h, openanything.DefaultErrorHandler())
seconddatastream = opener.open(request)
