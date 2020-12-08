class TestIterator:
    value = 0
    def next (self):
        '''
            python2 style
        '''
        self.value += 1
        if self.value > 10: raise StopIteration
        return self.value
    def __next__ (self):
        '''
            python3 style
        '''
        self.value += 1
        if self.value > 10: raise StopIteration
        return self.value
    def __iter__ (self):
        return self

ti = TestIterator()
for i in ti:
    print (i)

