loop()
{
	trap "echo 'How dare you!'" INT
	while true; do
		sleep 60
	done
}


trap "echo 'You hit control-C!'" INT

loop
