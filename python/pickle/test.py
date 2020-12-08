#!/usr/bin/env python

import pickle

class M(object):
    def __init__ (self, key, value):
        self.key = key
        self.value = value

m = M('hello', 'world')

d = pickle.dumps (m)
print (d)

m2 = pickle.loads (d)
print (m.key)
print (m.value)
