#usage: $0 <psw
readpasswd()
{
	while read name psw
	do
		printf "NAME: %-10s PSW: %s\n" "$name" "$psw"
	done
}

readpasswd2()
{
	while read name psw
	do
		printf "NAME: %-10s PSW: %s\n" "$name" "$psw"
	done
}<psw

readpasswd3()
{
	while read name psw
	do
		printf "NAME: %-10s PSW: %s\n" "$name" "$psw"
	done <psw
}

echo ====Version 1 ====
readpasswd <psw
echo ====Version 2 ====
readpasswd2
echo ====Version 3 ====
readpasswd3
echo ====Version 4 ====
{
	while read name psw
	do
		printf "NAME: %-10s PSW: %s\n" "$name" "$psw"
	done
} <psw
