items = [('name', 'Gumby'), ('age', 42)]
d = dict (items)
print (d)
d = dict (name='Gumby', age=42)
print (d)


# error
# print (d['nosuchitem'])
print (d.get('nosuchitem'))
print (d.get('nosuchitem', 'N/A'))

for k,v in d.items():
    print ("%s %s" % (k, v))

d.setdefault('nosuchkey', 'N/A')
print (d)
d['nosuchkey'] = 'really?'
d.setdefault('nosuchkey', 'N/A')
print (d)

