/*
Copyright © 2019 NAME HERE <EMAIL ADDRESS>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
package cmd

import (
	"github.com/spf13/cobra"
)

// putCmd represents the put command
var putCmd = &cobra.Command{
	Use:   "put <url>",
	Short: "HTTP PUT request",
	Long: `HTTP PUT request. For example:

mycurl put -d 'hello=world' http://localhost:8080/api/demo/demo
`,
	Args: urlValidator,
	Run: func(cmd *cobra.Command, args []string) {
		bodyReader, err := getDataReader()
		if err != nil {
			panic(err)
		}

		resp, err := newRequest("PUT", args[0], bodyReader)
		if err != nil {
			panic(err)
		}
		parseResponse((resp))

		closeDataReader(bodyReader)
	},
}

func init() {
	rootCmd.AddCommand(putCmd)

	registerDataParameter(putCmd)
	// Here you will define your flags and configuration settings.

	// Cobra supports Persistent Flags which will work for this command
	// and all subcommands, e.g.:
	// putCmd.PersistentFlags().String("foo", "", "A help for foo")

	// Cobra supports local flags which will only run when this command
	// is called directly, e.g.:
	// putCmd.Flags().BoolP("toggle", "t", false, "Help message for toggle")
}
