#!/bin/bash

func () 
{
	echo $#
	echo $*
	echo $@
}

func $*
func $@
func "$*"
func "$@"
func "abc def"
func '"abc" "def"'
