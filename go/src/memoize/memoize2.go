package main

import (
    "fmt"
    "bytes"
    "strings"
)

type memoizeFunction func (int) interface{}
var Fibonacci memoizeFunction
var RomanForDecimal memoizeFunction

func init() {
    Fibonacci = Memoize(func(x int) interface{} {
        if x < 2 {
            return x
        }
        return Fibonacci (x-1).(int) + Fibonacci(x-2).(int)
    })

    decimals := []int{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}
    romans := []string{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X",
        "IX", "V", "IV", "I"}
    RomanForDecimal = Memoize(func(x int) interface{} {
        if x < 0 || x > 3999 {
            panic("RomanForDecimal() only handles integers [0, 3999]")
        }
        var buffer bytes.Buffer
        for i, decimal := range decimals {
            remainder := x / decimal
            x %= decimal
            if remainder > 0 {
                buffer.WriteString(strings.Repeat(romans[i], remainder))
            }
        }
        return buffer.String()
    })
}

func main() {
    fmt.Println ("Fibonacci(45) =", Fibonacci(45).(int))
    x := 91
    fmt.Printf ("%4d = %s\n", x, RomanForDecimal(x).(string))
}

func Memoize (function memoizeFunction) memoizeFunction {
    cache := make(map[string]interface{})
    return func (x int) interface{} {
        key := fmt.Sprint(x)
        if value, found := cache[key]; found {
            return value
        }
        value := function (x)
        cache[key] = value
        return value
    }
}

