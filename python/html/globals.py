def foo(arg):
	x = 1
	print locals()
	locals()["x"] = 2
	print "x=", x

z = 7
print "z=", z
foo(3)
globals()["z"] = 8
print "z=", z
