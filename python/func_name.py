import inspect
def func():
    s = inspect.stack() 
    print s
    print s[0][3]

func()
