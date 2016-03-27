#!/usr/bin/python
#coding:utf-8

from urllib2 import Request, urlopen
from bs4 import BeautifulSoup


__metaclass__ = type

class Result:
	def __init__ (self, soup):
		h3 = soup.find ('h3')
		self.title = h3.a.string
		self.href = h3.a['href']
		
		# cite and dess were pre-formatted
		self.cite = soup.find(class_="_Rm")
		self.desc = soup.find(class_="st")


	def format (self):
		# weird
		print ('<section><a href="')
		print (self.href)
		print ('">')
		print (self.title.encode("utf-8"))
		print ("</a>")
		print (self.cite.encode("utf-8"))
		print (self.desc.encode("utf-8"))
		print ("</section>")
		#print ('<section><a href="%s">%s</a>%s%s</section>' % (repr(self.href), repr(self.title), repr(self.cite), repr(self.desc)))
		#print ("<section><a href=" + self.href + ">" + self.title + "</a>" + self.cite + self.desc + "</section>")
		
		pass


header="""<html lang="zh-CN">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
</head>
<body>"""

tail="""</body></html>"""

qs='https://www.google.com/search?q=Shenzhen&hl=zh'
request = Request (qs)
#request.add_header ('User-Agent', 'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0)')
request.add_header ('User-Agent', 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.75 Safari/537.36')


# ip5: user-agent:Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 Safari/601.1
# ip6: user-agent:Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 Safari/601.1
# GS5: user-agent:Mozilla/5.0 (Linux; Android 5.0; SM-G900P Build/LRX21T) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.23 Mobile Safari/537.36
# Linux: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.75 Safari/537.36


#request.add_header ('accept-language', 'zh-CN,zh')
#request.add_header ('accept-language', 'en-US,en')

response = urlopen(request)
html = response.read()
response.close()

#print (html)

gs=[]
ss=[]

soup = BeautifulSoup (html, "lxml")
resultStat = soup.find (id="resultStats")

# filter out the 'normal' result
srgs = soup.find(id="rso").find_all (class_="srg")
for srg in srgs:
	gs += srg.find_all (class_="g")

# format the ouput
for g in gs:
	s = Result (g)
	ss.append (s)

nav = soup.find (id="nav")


print (header)
print (resultStat)
#for g in gs:
#	print (g)
for s in ss:
	s.format()
print (nav)
print (tail)
