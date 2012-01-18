from SOAPpy import WSDL
wsdlFile = 'http://chennaiemergency.co.in/sree/s2.php?wsdl'
server = WSDL.Proxy (wsdlFile)
server.police (1.0, 2.0)
server.soapproxy.config.dumpSOAPOut = 1
server.soapproxy.config.dumpSOAPIn = 1
ret = server.police (1.0, 2.0)
print ret
