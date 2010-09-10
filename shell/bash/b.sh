func()
{
	num=$[$num + 1]
	echo $num
	if  [ "$num" == "3" ]
	then
		echo return 1
		return 1
	else
		echo return 0
		return 0
	fi
}

$num = 0

while true
do
	echo $num
	func
done

