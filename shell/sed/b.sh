sed -n '
	1, 100 {
		s/#.*//
		s/[ 	]*$//
		/^$/d
		p
	}
'
