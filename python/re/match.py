import re
m = re.match(r'www\.(.)*\..{3}', 'www.python.org')
print (m.group(1))
print (m.start(1))
print (m.end(1))
print (m.span(1))
