people = {
    'Alice': {
        'phone': '2341',
        'addr': 'Foo drive 23',
     },
    'Beth' : {
        'phone': '9102',
        'addr': 'Bar street 42',
     },
    'Cecil' : {
        'phone': '3158',
        'addr': 'Baz avenu 90'
     },
}

name = input ("name: ");

if name in people:
    print ("name: %s phone: %s addr: %s" % (name, people[name]['phone'], people[name]['addr']))
