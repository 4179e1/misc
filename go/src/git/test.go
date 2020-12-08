package main

import (
	"fmt"
	git "gopkg.in/src-d/go-git.v4"
)
func main() {
	fmt.Println("hello")

	repoPath := "/home/lyre/workspace/misc"
	repo, err := git.PlainOpen (repoPath)
	if err != nil {
		fmt.Println (err)
	}

	head, err := repo.Head()
	fmt.Println(head.Hash())

	commit, err := repo.CommitObject(head.Hash())
	fmt.Println (commit.Hash)
	fmt.Println (commit.Author.Name)
}
