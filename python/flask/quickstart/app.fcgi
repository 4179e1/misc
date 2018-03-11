#!/usr/bin/env python
# -*- coding: UTF-8 -*-

from cgi import escape
import sys, os
from flup.server.fcgi import WSGIServer
from flask import Flask
import GoogleParser

app = Flask (__name__)

@app.route ('/')
def index():
	return "Hello world!"

@app.route ('/search')
def search ():
	e500=""" <!DOCTYP html>
<html>
<head>
<title>500 Internal Server Error</title>
</head>
<body>
<h1>500 Internal Server Error</h1>
</body>
</html>
"""

	qs = environ['QUERY_STRING']

	return qs
#	try:
#		gp = GoogleParser.GoogleParser (qs)
#	except KeyError:
##		start_response('302 Found', [('Location', 'http://poetpalace.org/search.html')])
#		yield redirect ('http://poetpalace.org/search.html')
#	except Exception:
##		start_response('200 OK', [('Content-Type', 'text/html')])
#		import syslog
#		e = sys.exc_info()[0]
#		syslog.openlog ("search.py")
#		syslog.syslog(syslog.LOG_ERR, str(e))
#		syslog.closelog()
#		yiedl (e500)
#	except Excption as e:
##		start_response('200 OK', [('Content-Type', 'text/html')])
#		yield (repr (e))
#		
#
##	start_response('200 OK', [('Content-Type', 'text/html')])
#	for i in gp.iter():
#		yield (i)
	
if __name__ == '__main__':
	WSGIServer(app).run()

