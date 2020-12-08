import re
m = re.match(r'www\.(.*)\..{3}', 'www.python.org')
print (m.group(0))
print (m.group(1))
print (m.start(1))
print (m.end(1))
print (m.span(1))

def func1 (match):
    return 'Hello ' + match.group(1)

m = re.sub(r'www\.(.*)\..{3}', func1, 'www.python.org')
print (m)

def func2 (match):
    return 'Hello jython'

m = re.sub(r'www\.(.*)\..{3}', func2, 'www.python.org')
print (m)
