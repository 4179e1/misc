"""Convert to and from Roman numerals"""
import re

#Define exceptions
class RomanError (Exception): pass
class OutOfRangeError (RomanError): pass
class NotIntegerError (RomanError): pass
class InvalidRomanNumeralError (RomanError): pass

romanNumeralMap = (('M', 1000),
					('CM', 900),
					('D', 500),
					('CD', 400),
					('C', 100),
					('XC', 90),
					('L', 50),
					('XL', 40),
					('X', 10),
					('IX', 9),
					('V', 5),
					('IV', 4),
					('I', 1),
		)

def toRoman (n, debug=0):
	""" convert integer to Roman numeral"""
	if not (0 < n < 5000):
		raise OutOfRangeError, "number out of range (must be 1..3999)"
	if int (n) <> n:
		raise NotIntegerError, "non-integers can not be converted"

	result = ""
	for numeral, integer in romanNumeralMap:
		while n >= integer:
			result += numeral
			n -= integer
			if debug > 0:
				print 'subtracting', integer, 'from input, adding', numeral, 'to output'
	return result

#Define pattern to detect valid Roman numerals
#romanNumeralPattern = re.compile ('^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$')
romanNumeralPattern = re.compile ('''
	^			# beginning of string
	M{0,4}			# thousands - 0 to 4 M's
	(CM|CD|D?C{0,3})	# hundreds - 900 (CM), 400 (CD), 0-300(0 to 3 C's)
				#		or 500-800 (D, followed by 0 to 3 C's)
	(XC|XL|L?X{0,3})	# tens - 90 (XC), 40 (XL), 0-30 (0 to 3 X's)
				#		or 50-80 (L, followed by 0 to 3 X's)
	(IX|IV|V?I{0,3})	# ones - 9 (IX), 4 (IV), 0-3 (0 to 3 I's)
				#		or 5-8 (V, followed by 0 to 3 I's)
	$			# end of string
	''', re.VERBOSE)

def fromRoman (s, debug=0):
	""" convert Roman numeral to integer"""
	if not s:
		raise InvalidRomanNumeralError, "Input can not be blank"
	if not romanNumeralPattern.search (s):
		raise InvalidRomanNumeralError, 'Invalid Roman numeral: %s' % s

	result = 0
	index = 0
	for numeral, integer in romanNumeralMap:
		while s[index:index+len(numeral)] == numeral:
			result += integer
			index += len(numeral)
			if debug > 0:
				print 'found', numeral, 'of length', len(numeral), ', adding', integer
	return result


if __name__ == "__main__":
	print "call toRoman (1424)"
	toRoman (1424, 1)
	fromRoman ('MCMLXXII', 1)
