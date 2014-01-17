import launcelot

def handle_client (client_sock):
    try:
        while True:
            question = launcelot.recv_until (client_sock, '?')
            answer = launcelot.qadict.get (question, "I don't understand your question.")
            client_sock.sendall (answer)
    except EOFError:
        client_sock.close()

def server_loop (listen_sock):
    while True:
        client_sock, sockname = listen_sock.accept()
        handle_client (client_sock)

if __name__ == '__main__':
    listen_sock = launcelot.setup()
    server_loop (listen_sock)
