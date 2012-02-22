def make_counter(x):
	print 'entering make_counter'
	while 1:
		yield x
		print 'incrementing x'
		x = x + 1

counter = make_counter (2)
print counter
print counter.next()
print counter.next()
print counter.next()
