from SOAPpy import WSDL
wsdlFile = 'http://chennaiemergency.co.in/sree/s2.php?wsdl'
server = WSDL.Proxy(wsdlFile)
print server.methods.keys()

callInfo = server.methods['fire']
print callInfo.inparams[0].name
print callInfo.inparams[0].type

print callInfo.outparams[0].name
print callInfo.outparams[0].type
