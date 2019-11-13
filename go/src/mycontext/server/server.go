// The server program issues Google search requests and demonstrates the use of
// the go.net Context API. It serves on port 8080.
//
// The /search endpoint accepts these query params:
//   q=the Google search query
//   timeout=a timeout for the request, in time.Duration format
//
// For example, http://localhost:8080/search?q=golang&timeout=1s serves the
// first few Google search results for "golang" or a "deadline exceeded" error
// if the timeout expires.

package main

import (
	"fmt"
	"net/http"
	"context"
	"html/template"
	"log"
	"time"
	"mycontext/userip"
	"mycontext/google"
)

func main() {
	http.HandleFunc("/search", handleSearch)
	log.Fatal(http.ListenAndServe(":8080", nil))
}


// handleSearch handles URLs like /search?q=golang&timeout=1s by forwarding the
// query to google.Search. If the query param includes timeout, the search is
// canceled after that duration elapses.
func handleSearch (w http.ResponseWriter, req *http.Request) {
	var (
		ctx context.Context
		cancel context.CancelFunc
	)

	timeout, err := time.ParseDuration (req.FormValue ("timeout"))
	fmt.Println(timeout)
	if err == nil {
		// The request has a timeout, so create a context that is 
		// canceled automatically when the timeout expires
		ctx, cancel = context.WithTimeout (context.Background(), timeout)
	} else {
		ctx, cancel = context.WithCancel (context.Background())
	}
	defer cancel()  // Cancel ctx as soo as handleSearch returns.

	// Check the search query.
	query := req.FormValue ("q")
	if query == "" {
		http.Error (w, "no query", http.StatusBadRequest)
		return
	}

	// Store the user ip in ctx for use by code in other packages.
	userIP, err := userip.FromRequest (req)
	if err != nil {
		http.Error (w, err.Error(), http.StatusBadRequest)
		return
	}
	ctx = userip.NewContext (ctx, userIP)

	start := time.Now()
	results, err := google.Search (ctx, query)
	if err != nil {
		log.Println (err)
	}
	elapsed := time.Since (start)


	// hmm... define and init a anomyous struct here
	if err := resultsTemplate.Execute (w, struct {
		Results		google.Results
		Timeout, Elapsed time.Duration
	} {
		Results: results,
		Timeout: timeout,
		Elapsed: elapsed,
	}); err != nil {
		log.Print (err)
		return
	}
}


var resultsTemplate = template.Must(template.New("results").Parse(`
<html>
<head/>
<body>
  <ol>
  {{range .Results}}
    <li>{{.Title}} - <a href="{{.URL}}">{{.URL}}</a></li>
  {{end}}
  </ol>
  <p>{{len .Results}} results in {{.Elapsed}}; timeout {{.Timeout}}</p>
</body>
</html>
`))
