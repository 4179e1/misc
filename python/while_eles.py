from math import sqrt
for n in range(99,81,-1):
    root = sqrt(n)
    if root == int (root):
        print (root)
        break
else:
    print ("Didn't find it")
