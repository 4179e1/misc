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
	if not (0 < n < 4000):
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
romanNumeralPattern = '^M?M?M?(CM|CD|D?C?C?C?)(XC|XL|L?X?X?X?)(IX|IV|V?I?I?I?)$'

def fromRoman (s, debug=0):
	""" convert Roman numeral to integer"""
	if not s:
		raise InvalidRomanNumeralError, "Input can not be blank"
	if not re.search (romanNumeralPattern, s):
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
