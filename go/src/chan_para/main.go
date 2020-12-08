package main

import (
	"fmt"
	"time"
)

func report (i int) {
	fmt.Printf ("sleeped %d seconds\n", i)
}

func main () {
	ch := make (chan int)

	go func() {
		i := 3
		time.Sleep (time.Second * time.Duration(i))
		fmt.Println ("Sleeper done")
		ch <- i
	}()

	report (<-ch)

}

