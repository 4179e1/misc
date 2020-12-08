values=(39 5 36 12 9 3 2 30 4 18 22 1 28 225)
numvalues=${#values[@]}

for ((i=0; i < numvalues; i++));do
	lowest=$i
	for ((j=i; j < numvalues; j++));do
		if [ ${values[$j]} -le ${values[$lowest]} ]; then
			lowest=$j
		fi
	done

	temp=${values[$i]}
	values[$i]=${values[$lowest]}
	values[$lowest]=$temp

done

for (( i=0; i < numvalues; i++ ));do
	echo -ne "${values[$i]}\t"
done
echo
