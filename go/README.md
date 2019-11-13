## syntax

in, err := os.Open (infile)
out, err := os.Create (outfile) // ok, declare out, but only assins value to existing err

f, err := os.Open (infile)
f, err := os.Crate (outfile) // compile error

## map
m := make(map[strint]int)
m['abc'] += 1 // valid

## array & slice
a := [...]int{1,2,3}  // array
s := []int{1,2,3} // slice

## len
len() return *signed int*

## fmt
s := hello
fmt.Println ("%[1]s, %[1]s", s)

## iota
bitmap
const (
    lsb1 uint32 := 1 << iota
    lsb2
    lsb3
)

## utf8

Invalid utf8 char `\uFFFD`


## strings

`strings.join(list, separator)` python 的字符串join

## ioutil

`ioutil.ReadFile(filename)` 读取整个文件的内容`

## io
`io.WriteString` 直接往 `io.Writer` 接口写入string

`Write`方法本来接受的参数是`[]byte`

```go
type Writer interface {
    Write(p []byte) (n int, err error)
}
```