awk '
BEGIN 	{print "File\tOnwer"}\
			{print $8, "\t", $3} \
END		{print " - DONE - "} \
'
