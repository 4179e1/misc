import fileinput
for line in fileinput.input ():
    line = line.rstrip()
    num = fileinput.lineno()
    print ('%2i # %s' % (num, line))

