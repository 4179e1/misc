package main

import (
	"fmt"
	"math"
)

type Point struct{ X, Y float64 }

func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

func main() {
	p := Point{1, 2}
	q := Point{4, 6}
	mv := p.Distance

	fmt.Printf("%T\n", mv) // func(main.Point) float64
	fmt.Println(mv(q))

	me := Point.Distance
	fmt.Printf("%T\n", me) // func(main.Point, main.Point) float64
	fmt.Println(me(p, q))
}
