import sys, pprint, inspect
def tracer(frame, event, arg):
    print '------ Begin ------'
    pprint.pprint (frame)
    print '%s:%s():%d' % (frame.f_code.co_filename, frame.f_code.co_name, frame.f_lineno)
    #pprint.pprint (inspect.getmembers(frame))
    pprint.pprint (event) 
    pprint.pprint (arg) 
    print '------- End -------'
    return tracer

def main():
    print 'In main'
    for i in range(5):
        print i, i*3
    print 'done'

sys.settrace(tracer)
print 'hello'
main()
