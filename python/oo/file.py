f = open ("/Users/lyre/heroes4/01 The Preserve.mp3", "rb")

print f
print f.tell()
f.seek (-128, 2)
print f.tell()
tagData = f.read (128)
print tagData
print f.tell()

print f.closed
f.close()
print f.closed
print f
#it is ok
f.close()
