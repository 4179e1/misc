def faulty():
    raise Exception ("Something is wrong")

def ignore_exception():
    faulty()

def handle_exception():
    try:
        faulty()
    except:
        print ('oops, but we survived')
    
handle_exception()
ignore_exception()
