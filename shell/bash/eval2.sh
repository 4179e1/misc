mysort()
{
	if [ -n "$2" ]; then
		sort -nr $1 | head -$2
	else
		sort -nr $1
	fi
}

mysort psw 1

mysort2()
{
	eval sort -nr \$1 ${2:+"| head -\$2"}
}

mysort2 psw
mysort2 psw 1

