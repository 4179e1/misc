while [ -n "$(echo $1 | grep '-')" ]; do
	case $1 in
		-a)
			echo "aaahhh"
			;;
		-o)
			output=${2:?"need an argument"}
			echo $output
			;;
		-c)
			echo "ccc"
			;;
		*)
			echo "usage: ${0##*/} [-a] [-c] [-o op] args..."
			exit 1
			;;
	esac
	shift
done
