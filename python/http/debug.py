import httplib
httplib.HTTPConnection.debuglevel = 1
import urllib
feeddata = urllib.urlopen ('http://poetpalace.org/index.html').read()
