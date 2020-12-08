li = ['a', 'b', 'c']
for s in li:
	print s

print "\n".join(li)

for i in range(5):
	print i

# don't do this
li = ['a', 'b', 'c', 'd', 'e']
for i in range (len(li)):
	print li[i]


import os
for k, v in os.environ.items():
	print "%s=%s" % (k, v)

print "\n".join ([ "%s=%s" % (k, v) for k, v in os.environ.items()])

