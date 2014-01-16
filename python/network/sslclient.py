import os, socket, ssl, sys

try:
    script_name, hostname = sys.argv
except ValueError:
    sys.stderr.write ('usage: sslclient.py <hostname>')
    sys.exit(2)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect ((hostname, 443))

ca_certs_path = os.path.join (os,path.dirname(script_name), 'certfiles.crt')
sslsock = ssl.wrap_socket(sock, ssl_version=ssl.PROTOCOL_SSLv3, cert_reqs=ssl.CERT_REQUIRED, ca_certs=ca_certs_path)

try:
    ssl.match_hostname (sslsock.getpeercert(), hostname)
except ssl.CertificateError as ce:
    print ('Certificatie error:', str(ce))
    sys.exit (1)

sslsocket.sendall ('GET /HTTP/1.0\r\n\r\n')
result = sslsock.makefile().read()
sslsock.close()
print ('The document https://%s is %d bytes long' % (hostname, len(result)))

