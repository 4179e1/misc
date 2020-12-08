package main

import "fmt"

func f() (err error) {
	defer func() {
		if p := recover(); p != nil { // recover() return the panic value
			fmt.Printf("%T %[1]v\n", p) // string oops
			err = fmt.Errorf("internal error: %v", p)
		}
	}()

	panic("oops")

	return nil
}

func main() {
	err := f()
	if err != nil {
		fmt.Println(err)
	}
}
