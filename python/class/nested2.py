nested = [
[8,9],
['err']
]

'''
note that yeild != return.
When yeild a value, the next time you call the function, 
it continue from the line next to yield

for a recursive function, it have such behavior

enter func(depth=1)
    enter func(depth=2)
        enter func(depth=3)
leave func(depth=1)
    leave func(depth=2)
        leave func(depth=3)
'''

def flatten (nested, depth=0):
    depth += 1
    print (' '*4*depth, '=== entering flatten(', depth, ')  ===')
    print (' '*4*depth, 'nested = ', nested)
    try:
        try : nested + ''
        except TypeError: pass
        else: raise TypeError
        for sublist in nested:
            print (' '*4*depth, 'sublist', sublist)
            for element in flatten(sublist, depth):
                print (' '*4*depth, 'yeild element', element)
                yield element
                print (' '*4*depth, '=== leaving flatten(', depth, ') point 1 ===')
    except TypeError:
        print (' '*4*depth, 'type error, yield', nested)
        yield nested
        print (' '*4*depth, '=== leaving flatten(', depth, ') point 1 ===')

for num in flatten(nested):
    print ("------ yeild a element -------")
