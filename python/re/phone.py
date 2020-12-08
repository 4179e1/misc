"""
try to parse phone number like those:
	800-555-1212
	800 555 1212
	800.555.1212
	(800) 555-1212
	1-800-555-1212
	800-555-1212-1234
	800-555-1212x1234
	800-555-1212 ext. 1234
	work 1-(800) 555.1212 #1234
"""

import re
pattern = re.compile (r'^(\d{3})-(\d{3})-(\d{4})$')
print pattern.search ('800-555-1212').groups()

pattern = re.compile (r'^(\d{3})-(\d{3})-(\d{4})-(\d+)$')
print pattern.search ('800-555-1212-1234').groups()
print pattern.search ('800 555 1212 1234')
print pattern.search ('800-555-1212')

pattern = re.compile (r'^(\d{3})\D+(\d{3})\D+(\d{4})\D+(\d+)$')
print pattern.search ('800 555 1212 1234').groups()
print pattern.search ('800-555-1212-1234').groups()
print pattern.search ('80055512121234')
print pattern.search ('800-555-1212')

pattern = re.compile (r'^(\d{3})\D*(\d{3})\D*(\d{4})\D*(\d*)$')
print pattern.search ('80055512121234').groups()
print pattern.search ('800.555.1212.1234').groups()
print pattern.search ('800-555-1212').groups()
print pattern.search ('(800)-5551212 x1234')

pattern = re.compile (r'^\D*(\d{3})\D*(\d{3})\D*(\d{4})\D*(\d*)$')
print pattern.search ('(800)-5551212 x1234').groups()
print pattern.search ('800-555-1212').groups()
print pattern.search ('work 1-(800)-5551212 x1234')

# OK, it works
pattern = re.compile (r'(\d{3})\D*(\d{3})\D*(\d{4})\D*(\d*)$')
print pattern.search ('work 1-(800)-5551212 x1234').groups()
print pattern.search ('800-555-1212').groups()
print pattern.search ('80055512121234').groups()

pattern = re.compile (r'''
			# don't match beginning of string ,number can start anywhere
	(\d{3})	# area code is 3 digits (e.g. '800')
	\D*		# optional separator is any number of non-digits
	(\d{3})	# trunk is 3 digits (e.g. '555')
	\D*		# optional separator
	(\d{4})	# rest of number is 4 digits (e.g. '1212')
	\D*		# optional separator
	(\d*)	# extension is optional and can be any number of digits
	$		# end of string
	''', re.VERBOSE)

print pattern.search ('work 1-(800)-5551212 x1234').groups()
print pattern.search ('800-555-1212').groups()
