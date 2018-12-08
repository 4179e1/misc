package main

import (
	"fmt"
	"log"
	"reflect"
	pb	"pb/tutorial"
	"github.com/golang/protobuf/proto"
	"github.com/golang/protobuf/ptypes"
)

func main() {
	p := &pb.Person {
		Id: 1234,
		Name: "jdoe@example.com",
		Phones: []*pb.Person_PhoneNumber {
			{Number: "555-4321", Type: pb.Person_HOME},
		},
	}

	p.LastUpdated = ptypes.TimestampNow()

	fmt.Printf ("%V\n", p)
	fmt.Println (p.GetLastUpdated())

	out, err := proto.Marshal (p)
	if err != nil {
		log.Fatalln ("Failed to encode: ", err)
	}

	fmt.Println (out)

	p2 := &pb.Person{}
	if err := proto.Unmarshal (out, p2); err != nil {
		log.Fatalln ("Failed to parse: ", err)
	}

	fmt.Printf ("%V\n", p2)

	// I don't know why they were not equal...
	if ! reflect.DeepEqual (p, p2) {
		log.Fatalln ("Person mismatch")
	}
}
