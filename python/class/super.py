__metaclass__ = type

class Bird:
    def __init__ (self, arg=None):
        self.hungry = True
        if arg: print (arg)
    def eat(self):
        if self.hungry:
            print ("Aaaah...")
            self.hungry = False

class SongBird(Bird):
    def __init__ (self, arg=None):
        super(SongBird, self).__init__(arg)
        self.sound = 'Squawk!'
    def sing(self):
        print (self.sound)

sb = SongBird()
sb.sing()
sb.eat()
sb.eat()
sb = SongBird('silly bird...')
