function fib (n)
    if n < 2 then
        return 1 
    end
    return fib (n - 1) + fib (n - 1)
end

sum = fib (4)
print ("sum =", sum)
