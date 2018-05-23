package main

import (
    "fmt"
    "time"
)

func main () {
    ch := make (chan int, 1024)

    for i := 0; i < 4; i++ {
        ch <- i
    }

    go func () {
        time.Sleep (time.Second * 3)
        close (ch)
    } ()

    for {
        i, ok := <- ch
        if !ok {
            fmt.Println ("ch is not ok")
            break
        }
        fmt.Println (i)
        time.Sleep (time.Second * 1)
    }
}
