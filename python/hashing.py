#!/usr/bin/env python

import hashlib

def alpha_shard (word):
	if word[0] in 'abcdef':
		return 'server0'
	elif word[0] in 'ghijklm':
		return 'server1'
	elif word[0] in 'nopqrs':
		return 'server2'
	else:
		return 'server3'

def hash_shard (word):
	return 'server%d' % (hash(word) % 4)

def md5_shard (word):
	return 'server%d' % (ord(hashlib.md5(word).digest()[-1]) % 4)

words = open('/usr/share/dict/words').read().split()
for function in alpha_shard, hash_shard, md5_shard:
	d = {'server0': 0, 'server1': 0, 'server2': 0, 'server3': 0}
	for word in words:
		d[function(word.lower())] += 1
	print function.__name__[:-6], d
