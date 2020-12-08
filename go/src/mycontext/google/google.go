// Package google provides a function to do Google searches using the Google Web
// Search API. See https://developers.google.com/web-search/docs/
//
// This package is an example to accompany https://blog.golang.org/context.
// It is not intended for use by others.
//
// Google has since disabled its search API,
// and so this package is no longer useful.
package google

import (
	"context"
	"encoding/json"
	"net/http"
	"log"
	"fmt"
	"time"

	"mycontext/userip"
)

// Results is an ordered list of search results.
type Results []Result

// A Result contains the title and URL of a search result.
type Result struct {
	Title, URL string
}

func Search (ctx context.Context, query string) (Results, error) {
	// Prepare the Google Search API request.
	req, err := http.NewRequest ("GET", "https://ajax.googleapis.com/ajax/services/search/web?v=1.0", nil) 
	if err != nil {
		return nil, err
	}

	q := req.URL.Query()
	q.Set ("q", query)

	// If ctx is carrying the use rIP address, forward it to the server.
	// Google APIS us the use rIP to distinguish server-initiated rquests
	// from end-user request.
	if userIP, ok := userip.FromContext (ctx); ok {
		q.Set ("userip", userIP.String())
	}
	req.URL.RawQuery = q.Encode()
	log.Println (req.URL.RawQuery)


	// Issue the HTTP request and handle the response. The httpDo function
	// cancels the request if ctx.Done is closed.
	var results Results 
	err = httpDo (ctx, req, func (resp *http.Response, err error) error {
		// this function get called even if cancelled
		if err != nil {
			return err
		}
		defer resp.Body.Close()

		// Parse the JSON search result.
		// https://developers.google.com/web-search/docs/#fonje
		var data struct {
			ResponseData struct {
				Results []struct {
					TitleNoFormatting string
					URL					string
				}
			}
		}

		if err := json.NewDecoder (resp.Body).Decode (&data); err != nil {
			return err
		}
		log.Println (data)

		for _, res := range data.ResponseData.Results {
			results = append (results, Result {Title: res.TitleNoFormatting, URL: res.URL})
		}
		return nil
	})
	return results, err
}

// httpDo issues the HTTP request and calls f with the response. If ctx.Done is
// closed while the request or f is running, httpDo cancels the request, waits
// for f to exit, and returns ctx.Err. Otherwise, httpDo returns f's error.
func httpDo (ctx context.Context, req *http.Request, f func (*http.Response, error) error) error {
	// Run the HTTP request in a goroutine and pass the response to f.
	c := make (chan error, 1)
	req = req.WithContext (ctx)
	go func() {
		time.Sleep (time.Second * time.Duration (2))
		fmt.Println ("before timeout")
		c <- f (http.DefaultClient.Do (req)) // 发起请求
		fmt.Println ("after timeout")
	} ()

	select {
		case <- ctx.Done():
			<-c // Wait for f to return
			fmt.Println ("timed out")
			return ctx.Err()
		case err := <-c:
			return err
	}
}
