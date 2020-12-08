#!/usr/bin/env lua

sum = 0
num = 1

while num <= 100 do
    sum = sum + num
    num = num + 1
end
print ("sum =", sum)


-- 从1加到100
sum = 0
for i = 1, 100 do
    sum = sum + i
end
print ("sum =", sum)

-- 从1到100的奇数和
sum = 0
for i = 1, 100, 2 do
    sum = sum + i
end
print ("sum =", sum)

-- 从100到1的偶数和
sum = 0
for i = 100, 1, -2 do
    sum = sum + i
end
print ("sum =", sum)

-- until循环
sum = 2
repeat
   sum = sum ^ 2 --幂操作
   print(sum)
until sum >1000
