def repeater (value):
    while True:
        print ("before yield, value is ", value)
        new = (yield value)
        print ("after yield, new is ", new)
        if new is not None:
            print ('new is not none')
            value = new
            value+=1

r = repeater (42)
print (r.next())
print ('-----------------')
print (r.next())
print ('-----------------')
print (r.send(50))
print ('-----------------')
print (r.next())
