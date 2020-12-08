import sys, time, launcelot
from multiprocessing import Process
from simple import server_loop
from threading import Thread

WORKER_CLASSES = {'thread': Thread,
 'process': Process}

WORKER_MAX=10

def start_worker (Worker, listen_sock):		# Worker = Thread or Process
	worker = Worker (target=server_loop, args=(listen_sock, ))
	worker.start()
	return worker

if __name__ == '__main__':
	if len(sys.argv) != 3 or sys.argv[2] not in WORKER_CLASSES:
		print >>sys.stderr, 'usage: server_multi.py interface thread|process'
		sys.exit(2)
	Worker = WORKER_CLASSES[sys.argv.pop()]

	listen_sock = launcelot.setup()
	workers = []
	for i in range(WORKER_MAX):
		workers.append (start_worker(Worker, listen_sock))

	while True:
		time.sleep(2)

		for worker in workers:
			if not worker.is_alive():
				print worker.name, "died; starting replacement"
				workers.remove (worker)
				workers.append(start_worker(Worker, listen_sock))

