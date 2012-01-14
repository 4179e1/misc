# barced in curly brackets
d = {"server":"mpilgrim", "database":"master"}
print d
print d["server"]
print d["database"]
d["database"]="pubs"
d["uid"] = "sa"
print d
d = {}
print d
d["key"] = "value"
d["key"] = "other value"
d["Key"] = "Third value"
print d
d["retrycount"] = 3
d[42]="douglas"
print d
del d[42]
print d
d.clear()
print d
