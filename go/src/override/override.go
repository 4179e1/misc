package main

import (
    "fmt"
)

type MyChild struct {
    name string
}

func (c *MyChild) dump() {
    fmt.Printf ("Child %s\n", c.name)
}

func (c *MyChild) hello() {
    fmt.Printf ("Hello %s\n", c.name)
}

type MyParent struct {
    *MyChild
}

func (p *MyParent) dump() {
    fmt.Printf ("Parent %s\n", p.name)
}

func main () {
    c := &MyChild {"world"}
    c.dump()
    c.hello()

    p := &MyParent {c}
    p.dump()
    c.hello()

    fmt.Println (p)
}
