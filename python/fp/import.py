sys = __import__('sys')
os = __import__ ('os')
re = __import__ ('re')
unittest = __import__ ('unittest')

print sys
print os

moduleNames = ['sys', 'os', 're', 'unittest']
print moduleNames
modules = map(__import__, moduleNames)
print modules
print modules[0].version
import sys
print sys.version
