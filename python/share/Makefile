pre:
	rm -rf dir1 dir2
	-mkdir dir1 dir2
	echo 'test 1' > dir1/file1
	echo 'test 2' > dir2/file2

test:
	python simple_node.py http://localhost:4242 dir1 secret1 &	
	python simple_node.py http://localhost:4243 dir2 secret2 &
	python test.py
	ls -l dir1 dir2

kill:
	kill `ps -elf | grep 'python simple_node.py' | awk '{print $$4}'`
clean:
	rm -rf dir1 dir2
