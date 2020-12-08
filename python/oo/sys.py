import sys
print '\n'.join (sys.modules.keys())
print "fileinfo" in sys.modules.keys()
print "\n"
import fileinfo
print '\n'.join (sys.modules.keys())
print "fileinfo" in sys.modules.keys()
print fileinfo
print sys.modules["fileinfo"]

from fileinfo import MP3FileInfo
print MP3FileInfo.__module__
print sys.modules[MP3FileInfo.__module__]

