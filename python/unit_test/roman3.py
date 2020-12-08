"""Convert to and from Roman numerals"""
import re

#Define exceptions
class RomanError (Exception): pass
class OutOfRangeError (RomanError): pass
class NotIntegerError (RomanError): pass
class InvalidRomanNumeralError (RomanError): pass

#Roman numerals must be less than 5000
MAX_ROMAN_NUMERAL = 4999

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

#Create tables for fast conversion of roman numerals.
#See fillLookupTables() below
toRomanTable = [None] #Skip and index since Roman numerals have no zero
fromRomanTable = {}

def toRoman (n):
	""" convert integer to Roman numeral"""
	if not (0 < n < MAX_ROMAN_NUMERAL + 1):
		raise OutOfRangeError, "number out of range (must be 1..%s)" % MAX_ROMAN_NUMERAL
	if int (n) <> n:
		raise NotIntegerError, "non-integers can not be converted"
	return toRomanTable[n]

def fromRoman (s):
	""" convert Roman numeral to integer"""
	if not s:
		raise InvalidRomanNumeralError, "Input can not be blank"
	if not fromRomanTable.has_key(s):
		raise InvalidRomanNumeralError, 'Invalid Roman numeral: %s' % s
	return fromRomanTable[s]

def toRomanDynamic (n):
	"""convert integer to Roman numeral using dynamic programming"""
	result = ""
	for numeral, integer in romanNumeralMap:
		if n >= integer:
			result = numeral
			n -= integer
			break
	if n > 0:
		result += toRomanTable[n]
	return result

def fillLookupTables ():
	"""compute all the possible roman numerals"""
	#Save the values in two global tables to convert to and from integers.
	for integer in range (1, MAX_ROMAN_NUMERAL + 1):
		romanNumber = toRomanDynamic (integer)
		toRomanTable.append (romanNumber)
		fromRomanTable[romanNumber] = integer

fillLookupTables()


if __name__ == "__main__":
	print "call toRoman (1424)"
	print toRoman (1424)
	print fromRoman ('MCMLXXII')
