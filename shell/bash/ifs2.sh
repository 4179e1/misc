IFS=:

for dir in $PATH
do
	ls -ld $dir
done
