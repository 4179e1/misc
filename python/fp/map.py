def double(n):
	return n*2

li = [1, 2, 3, 5, 9, 10 ,256, -3]
print map (double, li)
print [double(n) for n in li]
newlist = []
for n in li:
	newlist.append(double(n))

print newlist

li = [5, 'a', (2, 'b')]
print map (double, li)
