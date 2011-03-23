PS4='$0 line $LINENO'
function errtrap
{
	es=$?
	echo "ERROR line $1: Command exited withe status $es"
}

function bad()
{
	return 17
}

trap 'errtrap $LINENO' ERR
bad
nosuchcommand
