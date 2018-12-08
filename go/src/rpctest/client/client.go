package main

import (
	"os"
_	"errors"
	"rpctest"
	"log"
	"net/rpc"
	"fmt"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Println ("usage: ", os.Args[0], "server:port")
		os.Exit (1)
	}
	
	serverAddrPort := os.Args[1]
	client, err := rpc.DialHTTP ("tcp", serverAddrPort)
	if err != nil {
		log.Fatal ("dialing:", err)
	}

	args := rpctest.Args{17, 8}
	var reply int
	err = client.Call ("Arith.Multiply", args, &reply)
	if err != nil {
		log.Fatal ("arith error:", err)
	}
	fmt.Printf ("Arith: %d*%d=%d\n", args.A, args.B, reply)

	var quot rpctest.Quotient
	err = client.Call ("Arith.Divide", args, &quot)
	if err != nil {
		log.Fatal ("arith error:", err)
	}
	fmt.Printf ("Arith: %d/%d=%d remainder %d\n", args.A, args.B, quot.Quo, quot.Rem)


    limit := 6
    done := make (chan bool, limit)

    sleepTest := func (a, b int) {
        args := rpctest.Args {
             A: a,
             B: b,
        }
        var reply int
        err := client.Call ("Arith.Concurrent", args, &reply)
        if err != nil {
            log.Fatal ("Arith Concurrent error:", err)
            done <- true
        } else {
            fmt.Printf ("Arith Concurrent %d\n", reply)
            done <- false
        }
    }

    for i := 1; i < limit; i++ {
        go sleepTest (1, i)
    }
    for i := 1; i < limit; i++ {
        <- done
    }
}
