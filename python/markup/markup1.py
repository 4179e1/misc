import sys, re
from util import *

print '<html><head><title>...</title></body>'

title = True
for block in blocks (sys.stdin):
    block = re.sub (r'\*(.+?)\*', r'<em>\1</em>', block)
    if title:
        print '<h1>%s</h1>' % block
        title = False
    else:
        print '<p>%s</p>' % block

print '</body></html>'
