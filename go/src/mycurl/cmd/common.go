package cmd

import (
	"bytes"
	"errors"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"os"
	"strings"

	"github.com/spf13/cobra"
	"github.com/spf13/viper"
)

func urlValidator(cmd *cobra.Command, args []string) error {
	if len(args) < 1 {
		return errors.New("requires url argument")
	}

	_, err := url.ParseRequestURI(args[0])
	if err != nil {
		return fmt.Errorf("Invalid url '%s'", args[0])
	}

	return nil
}

func newRequest(method string, url string, body io.Reader) (*http.Response, error) {
	client := &http.Client{}

	// new request
	req, err := http.NewRequest(method, url, body)
	if err != nil {
		return nil, err
	}

	// header
	for _, x := range headers {

		parts := strings.SplitN(x, ":", 2)
		k := strings.TrimSpace(parts[0])
		var v string
		if len(parts) == 2 {
			v = strings.TrimSpace(parts[1])
		}

		sugar.Debug(fmt.Sprintf("Header [%s] value [%s]", k, v))
		req.Header.Add(k, v)
	}

	const contentType = "Content-Type"
	const defaultContentType = "application/x-www-form-urlencoded"
	if req.Header.Get(contentType) == "" {
		req.Header.Add(contentType, defaultContentType)
		sugar.Debug(fmt.Sprintf("Header [%s] value [%s]", contentType, defaultContentType))
	}

	resp, err := client.Do(req)
	if err != nil {
		return nil, err
	}
	return resp, nil
}

func parseResponse(resp *http.Response) {

	include := viper.GetBool("include")
	if include {

		buf := bytes.NewBufferString(fmt.Sprintf("%s %s\n", resp.Proto, resp.Status))
		for k, v := range resp.Header {
			buf.WriteString(fmt.Sprintf("%s: %s\n", k, strings.Join(v, ", ")))
		}
		buf.WriteString("\n")
		io.Copy(os.Stdout, buf)
	}

	io.Copy(os.Stdout, resp.Body)

}

func registerDataParameter(cmd *cobra.Command) {
	cmd.Flags().StringP("data", "d", "", "<data>")
	viper.BindPFlag("data", cmd.Flags().Lookup("data"))
}

func getDataReader() (io.Reader, error) {
	dataVar := viper.GetString("data")

	if dataVar == "" {
		return nil, nil
	}

	// a file
	if dataVar[0] == '@' {
		f, err := os.Open(dataVar[1:])
		if err != nil {
			return nil, err
		}
		return f, nil
	}

	// a string
	return strings.NewReader(dataVar), nil
}

func closeDataReader(reader io.Reader) {
	switch reader.(type) {
	case *os.File:
		reader.(*os.File).Close()
	default:
	}
}
