def func1():
    a = 1
    _a = 2

    def func2():
        print a
        print _a

    return func2

f2=func1()
f2() #<=== a, _a in func1 are bound to func2
