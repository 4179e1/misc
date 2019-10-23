# The Go Programming Language

<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Program Sturcture](#program-sturcture)
  - [Reserved Names](#reserved-names)
  - [Declarations](#declarations)
  - [Variables](#variables)
    - [Short Variable Declarations](#short-variable-declarations)
    - [Pointers](#pointers)
    - [The new function](#the-new-function)
    - [Lifetime of Varianles](#lifetime-of-varianles)
  - [Assignments](#assignments)
    - [Tuple Assignments](#tuple-assignments)
    - [Assignability](#assignability)
  - [Type Declarations](#type-declarations)
  - [Packages and Files](#packages-and-files)
    - [Imports](#imports)
    - [Package Initialiation](#package-initialiation)
  - [Scope](#scope)
- [Basic Data Types](#basic-data-types)
  - [Intergers](#intergers)
  - [Floating-Point Numbers](#floating-point-numbers)
  - [Complex Numbers](#complex-numbers)
  - [Boolean](#boolean)
- [Strings](#strings)
  - [String Literals](#string-literals)
  - [Unicode](#unicode)
  - [UTF-8](#utf-8)
  - [Strings and Byte Slices](#strings-and-byte-slices)
  - [Conversions between Strings and Numbers](#conversions-between-strings-and-numbers)
  - [Constants](#constants)
    - [The Constant Generator iota](#the-constant-generator-iota)
    - [Untyped Constants](#untyped-constants)
- [Composite Types](#composite-types)
  - [Arrays](#arrays)
  - [Slices](#slices)
    - [The append Function](#the-append-function)
    - [In-Place Slice Techniques](#in-place-slice-techniques)
- [fmt](#fmt)

<!-- /code_chunk_output -->

## Program Sturcture

### Reserved Names

```
break        default      func         interface    select
case         defer        go           map          struct
chan         else         goto         package      switch
const        fallthrough  if           range        type
continue     for          import       return       var
```

[https://golang.google.cn/ref/spec#Keywords]

### Declarations

4 Kinds

- var
- const
- type 
- func 

### Variables

> If the expression is omitt ed, the initial value is the zero value for the typ e, which is 0 for numbers, **false** for boole ans, "" for str ings, and nil for int erfaces and reference typ es (slice, point er, map, channel, function)

#### Short Variable Declarations

`A short variable delaraiion does not necessaily declare all the variable on itss left-hand side. `But it should at least declare a new one.

```go
// Ok
in, err := os.Open(infile)
out, err := os.Open(outfile)
```

```go
f, err := os.Open(infile)
f, err := os.Create(outfile) // compile error: no new variables
```

#### Pointers

#### The new function

> The expression new(T) creates an unname d variab le of typ e T , initializes it to the zero value of T , and retur ns its address, which is a value of typ e *T .

```go
p := new(int)   // p, of type *int, points to an unnamed int variable
fmt.Println(*p) // "0"
*p = 2          // sets the unnamed int to 2
fmt.Println(*p) // "2"
```

#### Lifetime of Varianles

### Assignments

#### Tuple Assignments

```go
a[i], a[j] = a[j], a[i]
```

#### Assignability

### Type Declarations

```go
type Celsisus folat64
type Fahrenheit float64
```

### Packages and Files

#### Imports

#### Package Initialiation

### Scope

## Basic Data Types

Types:

- basic types
- aggregate types
- reference types
- interface types

### Intergers

rune == int32
byte == unit8
int != uint (same bits, but need explict onversion)

-5 % 3 = -2
-5 % -3 = -2

len() return `signed integer`

### Floating-Point Numbers

- float32
- float64, use this 

###  Complex Numbers

- complex64 (float32)
- complex128 (float64)

```go
var x = complex(1, 2)
y := 3 + 4i
```

### Boolean

x == true, or simply x 

short-circuit:
s != "" && s[0] == 'x'

## Strings

Immutable

### String Literals


> Raw str ing lit erals are a convenient way to write regular expressions, which tend to have lots of backsl ashes. They are also us eful for HTML templ ates, JSON lit erals, command usage messages, and the like, which often extend over multiple lines.

```go
const GoUsage = `Go is a tool for manging Go source code.

Usage:
    go command [arguments]
`
```

### Unicode

### UTF-8

binary | range  | values
-------|--------|---
0xxxxxx| runes 0−127 | (ASCII)
11xxxxx 10xxxxxx| 128−2047 |(values <128 unused)
110xxxx 10xxxxxx 10xxxxxx | 2048−65535 | (values <2048 unused)
1110xxx 10xxxxxx 10xxxxxx 10xxxxxx | 65536−0x10ffff | (other values unused)


```go
import "unicode/utf8"

s := "Hello, 世界"
fmt.Println(len(s)) // "13"
fmt.Println(utf8.RuneCountInString(s)) // "9"
```

![](./res/utf8.png)

### Strings and Byte Slices

> A string contains an array of bytes that, once created, is immutable. By contrast, the elements of a byte slice can be freely modified.

```go
s := "abc"
b := []byte(s)
s2 := string(b)
```

### Conversions between Strings and Numbers

```go
x := 123
y := fmt.Sprintf ("%d", x)
fmt.Println (y, strconv.Itoa(x)) // "123 123"


x, err := strconv.Atoi ("123") // x is int
y, err := strconv.ParseInt("123", 10, 64) // base 10, up to 64 bits
```

### Constants

#### The Constant Generator iota

```go
const (
    _ = 1 << (1 * iota)
    KiB  // 1024
    MiB  // 1024 * 1024
    GiB  // 1024 * 1024 * 1024
)
)
```

#### Untyped Constants

## Composite Types

- Array:  homogeneous data type, fixed size
- Slices & Maps: dynamic size


### Arrays

```go
var a [3]int
fmt.Println(a[0])
frmt.Println(a[len(a)-1])

// Index and elements
for i, v := range a {

}

// elements
for _, v := range a {

}

//auto size
q := [...]int{1, 2, 3}

type Currency int
const (
    USD Currency = iota
    EUR
    GBP
    RMB
)

symbol := [...]string{USD: "$", EUR: "e", GBP: "f", RMB: "y", 26: 'z'} // 27 elements
```

> 数组作为参数时是传值的（复制）

### Slices

![](./res/slice.png)

```go
// array
a := [...]int{1, 2, 3}
// slice
s := []int{1, 2, 3}

var s [] int    // len(s) == 0, s == nil
s = nil         // len(s) == 0, s == nil
s = []int(nil)  // len(s) == 0, s == nil
s = []int{}     // len(s) == 0, s != nil

// not s == nil
if len(s) == 0 {

}

make ([]T, len)
make ([]T, len, cap)
```

#### The append Function

![](res/slice2.png)

```go
var x []int
x = append (x, 1) // assign it back to x
```

#### In-Place Slice Techniques

```go
func noempty(strings []string) []string {
    i := 0
    for _, s := range strings {
        if s != "" {
            strings[i] = s
            i++
        }
    }
}

// stack
stack = append(stack, v)
top := stack[len(stack) - 1]
// stack shrink
stack = stack[:len(stack) - 1] // error if stack is empty


// preserve order
func remove(slice []int, i int) []int {
    copy(slice[i:], slice[i+1:])
    return slice[:len(slice)-1]
}

// out of order
func remove(slice []int, i int) []int {
    slice[i] = slice[len(i) - 1]
    return slice[:len(slice)-1]
}
```



## fmt

```go
ascii := 'a'
fmt.Printf ("%d %[1]c %[1]q\n", ascii) // 97 a 'a'
```