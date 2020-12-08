#!/bin/bash

do_array()
{
	for i in $*; do
		prog=${i#*:}
		pgopt=${i%%:*}
		echo $prog $pgopt
		sleep 1
	done
}

ARRAY=(
	o:gedit
	o:gvim
	ox:firefox
	)


do_array ${ARRAY[@]} &
echo "waiting..."
wait
