#!/bin/sh
#commet
#another
sed '\_#include <'"$1"'>_ {
	r '"$1"'
	d
}'
