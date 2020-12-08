def odd(n):
	return n % 2

li = [1, 2, 3, 5, 9, 10, 256, -3]
print filter (odd, li)
print [ e for e in li if odd(e)]
filteredList = []
for n in li:
	if odd(n):
		filteredList.append (n)
print filteredList
