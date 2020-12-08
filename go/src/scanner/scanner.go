package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

func main () {
    const input = "Now is the winter of our discotent,\nMade glorious summer by the sun of York.\n"

    scanner := bufio.NewScanner (strings.NewReader (input))
    scanner.Split (bufio.ScanLines)
    for scanner.Scan() {
        fmt.Println (scanner.Text())
    }
    if err := scanner.Err(); err != nil {
        fmt.Fprintln (os.Stderr, "reading input:", err)
    }

    scanner = bufio.NewScanner (strings.NewReader (input))
    scanner.Split (bufio.ScanWords)
    for scanner.Scan() {
        fmt.Println (scanner.Text())
    }
    if err := scanner.Err(); err != nil {
        fmt.Fprintln (os.Stderr, "reading input:", err)
    }

    scanner = bufio.NewScanner (strings.NewReader (input))
    scanner.Split (bufio.ScanBytes)
    for scanner.Scan() {
        fmt.Println (scanner.Text())
    }
    if err := scanner.Err(); err != nil {
        fmt.Fprintln (os.Stderr, "reading input:", err)
    }
}
