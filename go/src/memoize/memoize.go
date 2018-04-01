package main

import (
    "fmt"
)

type memoizeFunction func (int, ...int) interface{}
var Fibonacci memoizeFunction

func init() {
    Fibonacci = Memoize(func(x int, xs...int) interface{} {
        if x < 2 {
            return x
        }
        return Fibonacci (x-1).(int) + Fibonacci(x-2).(int)
    })
}

func main() {
    fmt.Println ("Fibonacci(45) =", Fibonacci(45).(int))
}

func Memoize (function memoizeFunction) memoizeFunction {
    cache := make(map[string]interface{})
    return func (x int, xs ...int) interface{} {
        key := fmt.Sprint(x)
        for _, i := range xs {
            key += fmt.Sprintf (",%d", i)
        }
        if value, found := cache[key]; found {
            return value
        }
        value := function (x, xs...)
        cache[key] = value
        return value
    }
}
