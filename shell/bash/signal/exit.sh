func ()
{
	exit
}

trap "echo 'oh no'" EXIT
func
echo "finish"
