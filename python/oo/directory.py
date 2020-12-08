import os
print os.path.join ("/Users/lyre/misc/python/", "fib.py")
print os.path.join ("/Users/lyre/misc/python", "fib.py")
print os.path.expanduser ("~")
print os.path.join (os.path.expanduser ("~"), "misc/python/fib.py")
print os.path.join (os.path.expanduser ("~"), "no/such/file")

#split
print os.path.split ("/Users/lyre/misc/python/fib.py")
(filepath, filename) = os.path.split ("/Users/lyre/misc/python/fib.py")
print "Path:%s Name:%s"  % (filepath, filename)
(shortname, extension) = os.path.splitext (filename)
print "Shortname: %s Extension: %s" % (shortname, extension)
