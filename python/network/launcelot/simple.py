'''
During load test, it's likely to get the following error:
[Errno 99] Cannot assign requested address 

Which is caused by TIME_WAIT.

There's a effcient way to recycle TIME_WAIT, but with potencial risks:
# echo 1 > /proc/sys/net/ipv4/tcp_tw_recycle
'''
import launcelot, socket

def handle_client (client_sock):
    try:
        while True:
            question = launcelot.recv_until (client_sock, '?')
            answer = launcelot.qadict.get (question, "I don't understand your question.")
            client_sock.sendall (answer)
    except (EOFError, socket.error):
        client_sock.close()

def server_loop (listen_sock):
    while True:
        client_sock, sockname = listen_sock.accept()
        handle_client (client_sock)

if __name__ == '__main__':
    listen_sock = launcelot.setup()
    server_loop (listen_sock)
