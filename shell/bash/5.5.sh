path=$PATH:

while [ $path ]; do
	ls -ld ${path%%:*}
	path=${path#*:}
done
