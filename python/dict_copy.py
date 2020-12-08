x = {}
y = x
x = {'username': 'admin', 'machine' : ['foo', 'bar', 'baz']}
print (x)
print (y)


# shallow copy
x = {'username': 'admin', 'machine' : ['foo', 'bar', 'baz']}
y = x.copy()
x['username'] = 'mlh'
print (x)
print (y)

y['machine'].remove('foo')
print (x)
print (y)

# deep copy
from copy import deepcopy
x = {'username': 'admin', 'machine' : ['foo', 'bar', 'baz']}
y = deepcopy (x)
x['machine'].append ('Foz')
print (x)
print (y)
