package main

import (
    "encoding/json"
    "io/ioutil"
    "fmt"
    "log"
)

func main() {
    var f map[string]interface{}
    input, err := ioutil.ReadFile ("./in.json")
    //input, err := os.Open ("./in.json")
    if err != nil {
        log.Fatal (err)
    }

    //reader = bufio.Reader 
    fmt.Println (string(input))

    if err := json.Unmarshal(input, &f); err != nil {
        log.Fatal (err)
    }
    fmt.Println (f)

    //fmt.Println ((f["float64"]).(float64) + 1)
    f["float64"] = f["float64"].(float64) + 1
    f["string"] = f["string"].(string) + " what?"
    for key,value := range f {
        //fmt.Printf ("%s: %v\n", key, value)
        fmt.Printf ("%s (%T): %v\n", key, value, value)
    }

    //output_bytes, err := json.Marshal (f)
    output_bytes, err := json.MarshalIndent (f, "", "   ")
    if err != nil {
        log.Fatal (err)
    }
    fmt.Println (string (output_bytes))

    if err := ioutil.WriteFile ("./out.json", output_bytes, 0644); err != nil {
        log.Fatal (err)
    }

}
