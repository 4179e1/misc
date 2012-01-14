# braced in square brackets
li = ["a", "b", "mpilgrim", "z", "example"]

li.append ("new");
li.insert (2, "new")
li.extend (["two", "element"])
print li

li = ['a', 'b', 'c']
li.extend(['d', 'e', 'f'])
print li, "length:", len(li)

li = ['a', 'b', 'c']
li.append(['d', 'e', 'f'])
print li, "length:", len(li)

li = ["a", "b", "mpilgrim", "z", "example"]
print li.index("example")
# error
#print li.index("c")
if "a" in li:
	print "index of a:", li.index("a")
if "c" in li:
	print "index of b:", li.index("c")

li.remove("z")
print li
print li.pop()
print li

li = li + ['example', 'new']
print li
li += ['two']
print li

li = [1, 2] * 3
print li
