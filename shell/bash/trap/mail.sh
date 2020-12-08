cleanup ()
{
	if [ -e $msgfile ]; then
		mv $msgfile dead.letter
	fi
	exit
}
trap cleanup INT TERM

msgfile=/tmp/msg$$

cat>$msgfile

# send the contents of $msgfile to specified mail address
sleep 60

rm $msgfile

trap - INT TERM
