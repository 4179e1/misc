li = [1, 9, 8, 4]
print [elem*2 for elem in li]
print li

params = {"server":"mpilgrim", "database":"master", "uid":"sa", "pwd":"secret"}
print params.keys()
print params.values()
print params.items()
print [k for k, v in params.items()]
print [v for k, v in params.items()]
print ["%s=%s" % (k, v) for k, v in params.items()]
