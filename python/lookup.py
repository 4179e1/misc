import sys

def init (data):
    data['first']={}
    data['middle']={}
    data['last']={}

def lookup (data, label, name):
    return data[label].get(name)

def store (data, *full_names):
    labels = ['first', 'middle', 'last']
    for full_name in full_names:
        print ('------', full_name, '-----')
        names = full_name.split()
        if len(names) >= 3:
            pass
        elif len(names) == 2:
            names.insert(1, '')
        elif len(names) == 1:
            names.append('')
            names.append('')
        else:
            print ("Error: Empty name")
            sys.exit(1)

        for label, name in zip (labels, names):
            print (label, name)
            # if data[label][name] == None, set it to [], and then append full_name
            data[label].setdefault(name, []).append(full_name)
            


if __name__ == '__main__' :
    data={}
    init (data)
    store (data, 'haha', 'hello world', 'how are you', 'how do you do', 'I am fine', 'thank you')
    print (lookup (data, 'first', 'how'))
    print (lookup (data, 'middle', 'are'))
    print (lookup (data, 'last', 'fine'))
    print (lookup (data, 'last', 'no'))

