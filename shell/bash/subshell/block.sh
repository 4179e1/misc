{
	hatter=mad
	trap "echo 'You hit CTRL-C'" INT
}

while true; do
	echo "\$hatter is $hatter"
	sleep 60
done
