class Rectangle:
    def __init__ (self):
        self.width=0
        self.height=0

    def __setattr__(self, name, value):
        if name == 'size':
            self.width, self.height = value
        elif name == 'width':
            self.width = value
        elif name == 'height':
            self.height = value
        else:
            self.__dict__[name] = value

    def __getattr__(self, name):
        if name == 'size':
            return self.width, self.height
        elif name == 'width':
            return self.width
        elif name == 'height':
            return self.height
        else:
            return self.__dict__[name]

r = Rectangle
r.size=150,100
print (r.size)
r.width=15
print (r.width)
r.height=10
print (r.height)
r.nop = 'nop'
print (r.nop)
# Exception
print (r.nosuch)
