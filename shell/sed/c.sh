sed '/INCLUDE/ {
	r test.txt
	d
}'
