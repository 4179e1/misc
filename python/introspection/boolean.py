print "and"
print 'a' and 'b'
print '' and 'b'
print 'a' and 'b' and 'c'

print "or"
print 'a' or 'b'
print '' or 'b'
print '' or [] or {}
def sidefx():
	print "in sidefx()"
	return 1
print 'a' or sidefx()

