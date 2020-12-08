__metaclass__ = type

class CounterList (list):
    def __init__ (self, *args):
        self.counter=0
        super(CounterList, self).__init__(*args)
    def __getitem__ (self, index):
        self.counter += 1
        return super(CounterList, self).__getitem__(index)

cl=CounterList(range(10))
print (cl)
cl.reverse()
del cl[3:6]
print (cl.counter)
print (cl[2] + cl[4])
print (cl.counter)
