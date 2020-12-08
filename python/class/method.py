__metaclass__ = type

class MyClass:
    number=0
    @staticmethod
    def smeth(arg):
        print ('This is a static method: ',  arg)

    @classmethod
    def cmeth(cls, arg):
        print ('This is a class method ', cls.number , arg)
        cls.smeth('lol')

MyClass.smeth('Hello')
MyClass.cmeth('world')

