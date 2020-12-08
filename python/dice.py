from random import randrange
num = int(input('How many dice? '))
sides = int(input ('How many sides per dice? '))
sum = 0
for i in range (num): sum += randrange (sides) + 1
print ("the result is", sum)
