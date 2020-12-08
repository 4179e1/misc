package main

import (
	"fmt"
	"io"
	"os"
	"reflect"
)

func main() {
	i := 3

	t := reflect.TypeOf(i)  // a reflect.Type
	fmt.Println(t.String()) // int
	fmt.Println(t)          // int

	var w io.Writer = os.Stdout
	fmt.Println(reflect.TypeOf(w)) // *os..File
	fmt.Printf("%T\n", w)          // *os.File

	v := reflect.ValueOf(i) // a reflect.Value
	fmt.Println(v)          // 3
	fmt.Printf("%v\n", v)   // 3
	fmt.Println(v.String()) // <int Value>

	t = v.Type()            // a reflect.Type
	fmt.Println(t.String()) // int

	x := v.Interface()    // an interface{}
	d := x.(int)          // an int
	fmt.Printf("%d\n", d) // 3
}
