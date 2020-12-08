makecmd ()
{
	read target colon src
	
	for src in $src; do
		if [ $src -nt $target ]; then
			while read cmd && $(echo "$cmd" | grep "\t*" ) ;do
				echo "$cmd"
				eval ${cmd#\t}
			done
			break
		fi
	done
}<Makefile

makecmd
