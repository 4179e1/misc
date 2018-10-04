package main

import (
    "fmt"
    "time"
)

func main () {
    ch := make (chan int, 1024)
    done := make (chan bool)


    go func () {
        time.Sleep (time.Second * 3)
        close (done)
    } ()

    for i := 0; i < 128; i++ {
        ch <- i


        select {
        case v, ok := <- ch:
            if !ok {
                fmt.Printf ("ch is %v\n", ok)
                break
            }
            fmt.Println (v)
            time.Sleep (time.Second * 1)
        case <- done:
            fmt.Println ("DONE")
        }
    }
}
