ignorehup()
{
	trap "" HUP
	eval "$@"
}

ignorehup "$@"
