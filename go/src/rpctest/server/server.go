package main

import (
	"net/rpc"
	"net/http"
	"rpctest"
	"fmt"
)

/*
func (t *rpctest.Arith) Multiply (args *rpctest.Args, reply *int) error {
	*reply = args.A * args.B
	return nil
}

func (t *rpctest.Arith) Divide (args *rpctest.Args, quo *rpctest.Quotient) error {
	if args.B == 0 {
		return errors.New ("divide by zero")
	}

	quo.Quo = args.A / args.B
	quo.Rem = args.A % args.B
	return nil
}
*/

func main() {
	arith := new (rpctest.Arith)
	rpc.Register (arith)
	rpc.HandleHTTP()

	err := http.ListenAndServe (":1234", nil)
	if err != nil {
		fmt.Println (err.Error())
	}

}
