echo 'Select a directory:'
done=false

IFS=:

while [ $done = false ];do
	num=1
	for direc in $PATH;do
		echo $num')' $direc
		num=$((num+1))
	done

	echo -n 'directory?'
	read REPLY

	if [ $REPLY -lt $num ] && [ $REPLY -gt 0 ];then
		set - $DIR_STACK
		break
	else
		echo 'invalid selection.'
	fi
done
