__metaclass__ = type

class Person:
    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name
    
    def greet(self):
        print ("Hello, world! I'm %s." % self.name)

if __name__ == '__main__':
    p = Person()
#    p.greet()
    p.setName('lol')
    print (p.getName())
    p.greet()
