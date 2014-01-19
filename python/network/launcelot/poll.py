import launcelot
import select

listen_sock = launcelot.setup()
sockets = {listen_sock.fileno(): listen_sock}
requests = {}
responses = {}

poll = select.poll()
poll.register (listen_sock, select.POLLIN)

while True:
	for fd, event in poll.poll():
		sock = sockets[fd]
		if event & (select.POLLHUP | select.POLLERR | select.POLLNVAL):
			poll.unregister(fd)
			del sockets[fd]
			requests.pop (sock,None)
			responses.pop (sock, None) 

		elif sock is listen_sock:
			newsock, sockname = sock.accept()
			newsock.setblocking (False)
			fd = newsock.fileno()
			sockets[fd] = newsock
			poll.register (fd, select.POLLIN)
			requests[newsock] = ''				# init request, so that it can use + method later

		elif event & select.POLLIN:
			data = sock.recv(4096).strip('\n')
			if not data:
				sock.close()
				continue
			requests[sock] += data				# add to request
			if '?' == requests[sock][-1]:
				question = requests.pop(sock)
				answer = launcelot.qadict.get(question, "I don't understand your question.")
				poll.modify (sock, select.POLLOUT)
				responses[sock] = answer		# add response
		elif event & select.POLLOUT:
			response = responses.pop (sock)		# remove response
			n = sock.send (response)
			if n < len(response):
				responses[sock] = response[n:]	# add undone response
			else:
				poll.modify(sock, select.POLLIN)
				requests[sock] = ''				# remove request
				
