package main

import (
	"os"
	"log"
)

func main () {
	logger := log.New (os.Stderr, "[test] ", log.LstdFlags)
	logger.Println ("hello")
    logger.SetFlags(logger.Flags() | log.Lmicroseconds | log.Lshortfile)
	logger.Println ("world")
	for i := 0; i < 10; i++ {
		logger.Println (i)
	}
}
