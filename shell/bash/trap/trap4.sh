loop()
{
	trap "echo 'How dare you!'" INT
}


trap "echo 'You hit control-C!'" INT

loop

while true; do
	sleep 60
done
