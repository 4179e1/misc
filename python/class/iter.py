class Fibs:
    def __init__ (self):
        self.a = 0
        self.b = 1
    def __next__ (self):
        self.a, self.b = self.b, self.a + self.b
        return self.a
    def next (self):
        self.a, self.b = self.b, self.a + self.b
        return self.a
    def __iter__ (self):
        return self

fib = Fibs()
print ("fib: ", fib.a, fib.b)
print ("next(fib):", next(fib))
print ("next(fib):", next(fib))
print ("next(fib):", next(fib))

for f in fib:
    print (f)
    if f >= 10:
        break
