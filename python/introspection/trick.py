# "trick"
a = "first"
b = "second"
#( ( 1 and a) or b )
print 1 and a or b
print 0 and a or b

# "error"
a = ""
b = "second"
print 1 and a or b

# safe
print (1 and [a] or [b])[0]

