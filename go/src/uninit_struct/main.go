package main

import "fmt"

type Point struct {
	x int
	y int
}

type Circle struct {
	p Point
	radius int
}

func main() {
	c := Circle{}

	fmt.Println (c)
	fmt.Println (c.p.x)
}
