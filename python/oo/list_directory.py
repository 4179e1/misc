import os
print os.listdir ("/Users/lyre/heroes4")
dirname="/Users/lyre"
print os.listdir (dirname)
print [f for f in os.listdir(dirname)
	if os.path.isfile(os.path.join (dirname, f))]
print [f for f in os.listdir (dirname)
	if os.path.isdir (os.path.join (dirname, f))]

