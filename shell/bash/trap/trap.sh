trap "echo 'You hit control-C!'" INT
trap "echo 'You tried to kill me!'" TERM
while true; do
	sleep 60
done
