import fileinput, re

pat = re.compile(r'From: (.*) <.*?>$')
for line in fileinput.input():
    m = pat.match(line)
    if m: print (m.group(1))
