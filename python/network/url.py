from urllib import urlopen
page = urlopen('http://www.python.org')
text = page.read()
print (text)

# download
# from urllib import urlretrieve
# urlretrieve ('http://www.python.org', '/tmp/test')
