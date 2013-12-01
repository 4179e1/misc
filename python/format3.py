format = "Hello, %s. %s enough for ya?"
values = ('world', 'hot')
print (format % values)

#substitute
from string import Template
s = Template ("$x, it's ${y}tastic!")
t = s.substitute(x='Hi', y='slurm')
print (t)

s = Template ('A $thing must never $action.')
d = {'thing': 'gentleman',
    'action': 'show his socks'}
print (s.substitute (d))

s = 'A %(thing)s must never %(action)s.'
print (s % d)
