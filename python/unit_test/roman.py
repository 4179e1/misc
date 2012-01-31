"""Convert to and from Roman numerals"""
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
	result = ""
	for numeral, integer in romanNumeralMap:
		while n >= integer:
			result += numeral
			n -= integer
			if debug > 0:
				print 'subtracting', integer, 'from input, adding', numeral, 'to output'
	return result


def fromRoman (s):
	""" convert Roman numeral to integer"""
	pass

if __name__ == "__main__":
	print "call toRoman (1424)"
	toRoman (1424, 1)
