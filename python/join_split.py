params = {"server":"mpilgrim", "database":"master", "uid":"sa", "pwd":"secret"}
s = ";".join ( ["%s=%s" % (k, v) for k, v in params.items()])
print s
print s.split(";");
print s.split(";", 1);
