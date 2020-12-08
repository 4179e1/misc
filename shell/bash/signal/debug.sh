function dbgtrap
{
	echo "badvar is $badvar"
}

trap dbgtrap DEBUG

badvar=1
cd
badvar=orz
trap - DEBUG
