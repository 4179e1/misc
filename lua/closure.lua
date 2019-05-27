function newCounter()
    local i = 0
    return function()     -- anonymous function
       i = i + 1
        return i
    end
end
 
c1 = newCounter()
print(c1())  --> 1
print(c1())  --> 2

c2 = newCounter()
print (c2())


function myPower(x)
    return function (y) 
        return y^x
    end
end

mp3 = myPower(3)
print (mp3(2))

print (myPower(4)(2))

function foo(x) return x^2 end
foo = function(x) return x^2 end
