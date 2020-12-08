pre:
	rm -rf dir1 dir2 client
	-mkdir dir1 dir2 client
	echo 'test 1' > dir1/file1
	echo 'test 2' > dir2/file2

test:
	python test.py
	ls -l dir1 dir2

client:
	python client.py server.met client http://localhost:4244

v1:
	python simple_node.py http://localhost:4242 dir1 secret1 &	
	python simple_node.py http://localhost:4243 dir2 secret2 &

v2:
	python simple_node_v2.py http://localhost:4242 dir1 secret1 &	
	python simple_node_v2.py http://localhost:4243 dir2 secret2 &

kill:
	kill `ps -elf | grep 'python simple_node.*.py' | awk '{print $$4}'`
clean:
	rm -rf dir1 dir2 client
