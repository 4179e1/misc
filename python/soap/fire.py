from SOAPpy import SOAPProxy
url = 'http://chennaiemergency.co.in/sree/s2.php'
namespace = 'urn:ChnEmergency'
server = SOAPProxy (url, namespace)
server.config.dumpSOAPOut = 1
server.config.dumpSOAPIn = 1
r = server.fire (1.0, 2.0)
print dir (r)
