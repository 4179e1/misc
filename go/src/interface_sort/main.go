package main

import (
	"fmt"
	"sort"
)

func mysort(a []interface{}) []interface{} {
	// convert a from interface{} to int slice
	n := make([]int, 0, len(a))
	for _, x := range a {
		n = append(n, x.(int))
	}

	sort.Ints(n)

	// convert a back to int slice from interface{}
	r := make([]interface{}, 0, len(a))
	for _, x := range n {
		r = append(r, x)
	}
	return r
}

func main() {
	m := make(map[interface{}]interface{})

	m[1] = "a"
	m[2] = "b"
	m[3] = "c"
	m[4] = "d"
	m[5] = "e"
	m[26] = "z"

	fmt.Println(m)

	// use map to generate a random order slice
	a := make([]interface{}, 0, len(m))
	for k := range m {
		a = append(a, k)
	}

	fmt.Println(a)
	//a = mysort (a)
	sort.Slice(a, func(i, j int) bool {
		return a[i].(int) < a[j].(int)
	})
	fmt.Println(a)

}
