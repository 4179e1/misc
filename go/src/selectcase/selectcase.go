package main
import (
    "fmt"
    "reflect"
	"time"
)

func main(){
    var n int = 3
    var chs = make([]chan int, n)
    
    var worker = func(n int, c chan int){
        c<-n
        //close(c)
    }
    
    //不定数量的channel数组
    for i:=0;i<n;i++{
        chs[i]=make(chan int)
        go worker(i, chs[i])
    }

	go func() {
		time.Sleep (time.Second * 3)
		for i:=0; i<n; i++ {
			close (chs[i])
		}
	}()
    

    var selectCase = make([]reflect.SelectCase, n)
    //将channel绑定到SelectCase
    for i:=0;i<n;i++{
        selectCase[i].Dir = reflect.SelectRecv //设置信道是接收,可以为下面值之一
        /*
        const (
            SelectSend    SelectDir // case Chan <- Send
            SelectRecv              // case <-Chan:
            SelectDefault           // default
        )
        */
        selectCase[i].Chan = reflect.ValueOf(chs[i])
    }
    
    for  {
        chosen, recv, recvOk := reflect.Select(selectCase)
        if recvOk {
            fmt.Println(chosen, recv.Int(), recvOk)
        }else{
            fmt.Println(chosen, " recv error")
			break
        }
    }
}
