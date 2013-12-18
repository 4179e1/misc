class Calculator:
    def calculate (self, expression):
        self.value = eval (expression)

class Talker:
    def talk(self):
        print 'Hi, my values is', self.value

class TalkingCalculator(Calculator,Talker):
    pass

tc = TalkingCalculator()
tc.calculate('1+2*3')
tc.talk()

print (hasattr(tc,'talk'))
print (hasattr(tc,'nop'))
m1 = getattr(tc,'talk')
m2 = getattr(tc,'nop', None)
print (m1)
print (m2)
print (hasattr(m1, '__call__'))
print (hasattr(m2, '__call__'))
