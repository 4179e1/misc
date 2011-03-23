#!/bin/bash
set -o functrace
function returntrap
{
	echo "A return occurred"
}

trap returntrap RETURN

function hello
{
	echo "hello world"
}

. ~/.bashrc
hello
source ~/.bashrc
