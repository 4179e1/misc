BEGIN {
		# prompt user to enter a number
	printf ("Enter number: ")
}

$1 ~ /^[0-9]+$/ {
	number = $1
	if (number == 0)
		fact = 1
	else
		fact = number
	
	for (x = number - 1; x > 1; x--)
			fact *= x
	
	printf ("The factorial of %d is %g\n",  number, fact)
	exit
}

{ printf ("\nInvalid entry. Enter a nunber:")}
