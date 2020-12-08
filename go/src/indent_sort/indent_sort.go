package main

import (
    "sort"
    "fmt"
    "strings"
)

var original = []string{
    "Nonmetals",
    "    Hydrogen",
    "    Carbon",
    "    Nitrogen",
    "    Oxygen",
    "Inner Transitionals",
    "    Lanthanides",
    "        Europium",
    "        Cerium",
    "    Actinides",
    "        Uranium",
    "        Plutonium",
    "        Curium",
    "Alkali Metals",
    "    Lithium",
    "    Sodium",
    "    Potassium",
}


func main() {
    fmt.Println("|     Original      |       Sorted      |")
    fmt.Println("|-------------------|-------------------|")

    sorted := sortedIndentedStrings(original)
    for i:= range original {
        fmt.Printf ("|%-19s|%-19s|\n", original[i], sorted[i])
    }
}

type Entry struct {
    key string
    value   string
    children Entries
}

type Entries []Entry

func (entries Entries) Len() int {return len(entries)}
func (entries Entries) Less(i, j int) bool {
    return entries[i].key < entries[j].key
}
func (entries Entries) Swap (i, j int) {
    entries[i], entries[j] = entries[j], entries[i]
}

func sortedIndentedStrings (slice []string) []string {
    entries := populateEntries(slice)
    //fmt.Printf ("%+v\n", entries)
    return sortedEntries(entries)
}

func populateEntries (slice []string) Entries {
    indent, indentSize := computeIndent(slice)
    //fmt.Printf ("`%s', %d\n", indent, indentSize)
    entries := make(Entries, 0)
    for _, item := range slice {
        i, level := 0, 0
        for strings.HasPrefix(item[i:], indent) {
            i += indentSize
            level++
        }
        //fmt.Printf ("`%s', %d, %d\n", item, i, level)
        key := strings.ToLower(strings.TrimSpace(item))
        addEntry (level, key, item, &entries)
    }
    return entries
}

func computeIndent (slice []string) (string, int){
    for _, item := range slice {
        if len(item) > 0 && (item[0] == ' ' || item[0] == '\t') {
            whitespace := rune(item[0])
            //for i, char := range item[1:] {
            for i, char := range item {
                if char != whitespace {
                    indent := strings.Repeat(string(whitespace), i)
                    return indent,i
                }
            }
        }
    }
    return "", 0
}

func addEntry (level int, key, value string, entries *Entries) {
    if level == 0 {
        *entries = append (*entries, Entry{key, value, make(Entries, 0)})
    } else {
        addEntry (level-1, key, value, &((*entries)[entries.Len() - 1].children))
    }
}

func sortedEntries (entries Entries) [] string {
    var indentedSlice []string
    sort.Sort (entries)
    for _, entry:= range entries {
        populateIndentedStrings(entry, &indentedSlice)
    }
    return indentedSlice
}

func populateIndentedStrings (entry Entry, indentedSlice *[]string) {
    *indentedSlice = append (*indentedSlice, entry.value)
    sort.Sort(entry.children)
    for _,child := range entry.children {
        populateIndentedStrings (child, indentedSlice)
    }
}
