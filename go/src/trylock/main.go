package main

import (
	"log"
	"time"
)

var lockch chan bool

func task(name string, second int) {
	select {
	case lockch <- true:
		log.Printf("%s get lock", name)
		time.Sleep(time.Second * time.Duration(second))
		log.Printf("%s done", name)
		<-lockch
	default:
		log.Printf("%s Unable to get lock", name)
		time.Sleep(time.Second * time.Duration(second))
	}
}

func long() {
	for {
		task("long", 3)
	}
}

func short() {
	for {
		task("short", 1)
	}

}

func main() {
	lockch = make(chan bool, 1)

	go long()
	go short()

	select {}
}
