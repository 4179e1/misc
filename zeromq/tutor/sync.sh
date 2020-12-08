echo "Starting subscribers..."
for a in `seq 1 10`; do
	./syncsub &
done
echo "Starting publisher..."
./syncpub
