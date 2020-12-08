package main

import (
    "fmt"
    "time"
)

func main () {
    // see the difference of cap 0 and 1
    ch := make (chan int, 1)

    go func () {
        time.Sleep (10 * time.Second)
        fmt.Println ("Goroutine wake up, comsuing")
        _ = <- ch
    }()

    
    ch <- 10
    fmt.Println ("Main routine sent a value")
}

