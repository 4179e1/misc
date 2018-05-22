package main

import (
    "fmt"
)

func main() {
    var a uint8
    var b uint8
    a = 254
    b = 254
    for  i := 0; i <= 256; i++ {
        fmt.Printf ("Unsigned: %d - %d = %d , Signed: %d - %d = %d\n", int(a), int(b), int(a)-int(b), int8(a), int8(b), int8(int8(a) - int8(b)))
        a++
    }
}
