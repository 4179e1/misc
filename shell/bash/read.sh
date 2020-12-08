#shell convenion dictates that prompts should go to stderr.
echo -n 'terminal?' >&2
read TERM
echo "TERM is $TERM"
