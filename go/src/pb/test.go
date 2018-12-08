package main

import (
	"fmt"
	pb	"pb/tutorial"
	"github.com/golang/protobuf/ptypes"
)

func main() {
	p := pb.Person {
		Id: 1234,
		Name: "jdoe@example.com",
		Phones: []*pb.Person_PhoneNumber {
			{Number: "555-4321", Type: pb.Person_HOME},
		},
	}

	p.LastUpdated = ptypes.TimestampNow()

	fmt.Println (p)
	fmt.Println (p.GetLastUpdated())
}
