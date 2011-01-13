while getopts ":ab:c" opt
do
	echo $opt
	case $opt in
		a)
			echo "a";;
		b)
			echo "b $OPTARG";;
		c)
			echo "c";;
		\?)
			echo "usage: ${0##.*/} [-a] [-b barg] [-c] args..."
			exit 1
	esac
done

shift $(($OPTIND - 1))
