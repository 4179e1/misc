package main

import (
	"log"
	"net/http"
	"time"
)

type timeHandler struct {
	format string
}

func (th *timeHandler) ServeHTTP (w http.ResponseWriter, r *http.Request) {
	tm := time.Now().Format(th.format)
	w.Write ([]byte("The time is: " + tm))
}

func timeHandlerFunc (w http.ResponseWriter, r *http.Request) {
	tm := time.Now().Format (time.RFC1123)
	w.Write ([]byte("The time is: " + tm))
}

func getTimeHandlerFunc (format string) http.Handler {
	fn := func (w http.ResponseWriter, r *http.Request) {
		tm := time.Now().Format (format)
		w.Write ([]byte("The time is: " + tm))
	}

	return http.HandlerFunc (fn)
}

func main() {
	mux := http.NewServeMux()

	// Redirect Handler
	rh := http.RedirectHandler ("http://www.qq.com", 307)
	mux.Handle ("/foo", rh)

	// Custom Handler
	th1123 := &timeHandler{format: time.RFC1123}
	mux.Handle("/time/rfc1123", th1123)

	th3339 := &timeHandler{format: time.RFC3339}
	mux.Handle("/time/rfc3339", th3339)

	// Custom Handler Func
	th1 := http.HandlerFunc (timeHandlerFunc)
	mux.Handle ("/time1", th1)

	// Shortcut for the 2 lines above
	mux.HandleFunc ("/time2", timeHandlerFunc)

	// Closure
	th3 := getTimeHandlerFunc (time.RFC1123)
	mux.Handle ("/time3", th3)


	log.Println ("Listending...")
	http.ListenAndServe (":3000", mux)
}
