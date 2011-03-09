names=(hatter [5]=duchess alice)

for i in "${names[@]}"
do
	echo $i
done

for i in "${names[*]}"
do
	echo $i
done

echo inedex: ${!names[@]}

echo size of names: ${#names[@]}
echo size of names[0]: ${#names[0]}

names=([100]=tweedledee tweedledum)
for i in "${names[*]}"
do
	echo $i
done

unset names[100]
#unset entire array
unset names
