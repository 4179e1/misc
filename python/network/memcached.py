import memcache, random, time, timeit, sys

mc = memcache.Client(['127.0.0.1:11211'])

def compute_square (n):
	value = mc.get('sq:%d' % n)
	if value is None:
		time.sleep (0.001) # pretend that computing a squrae is expensive
		value = n*n
		if not mc.set ('sq:%d' % n, value):
			print 'error, is memcached running?'
			sys.exit (1)
	return value

def make_request():
	compute_square (random.randint(0,5000))

print 'Ten Successive runs:'

for i in range (10):
	print '%.2fs' % timeit.timeit(make_request, number=2000)
print
