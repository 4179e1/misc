for i in $(cut -f 1,3 -d: /etc/passwd);do
	array[${i#*:}]=${i%:*}
done

echo "User ID $1 is ${array[$1]}."
echo "There are currently ${#array[@]} user accounts on the system."
