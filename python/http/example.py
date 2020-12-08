import openanything
useragent = 'MyHTTPWebServicesApp/1.0'
url = 'http://poetpalace.org/redirect.html'
params = openanything.fetch (url, agent=useragent)
print params
if params['status'] == 301:
	url = params['url']

newparams = openanything.fetch (url, params['etag'], params['lastmodified'], useragent)
print newparams
