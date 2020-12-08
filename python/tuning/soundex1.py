# Woo             W000 12.156329155
# Pilgrim         P426 16.1293921471
# Flingjingwalker F452 22.1297280788

import string, re

charToSoundex = {
	"A":"9",
	"B":"1",
	"C":"2",
	"D":"3", 
	"E":"9" ,
	"F":"1", 
	"G":"2" ,
	"H":"9" ,
	"I":"9" ,
	"J":"2" ,
	"K":"2" ,
	"L":"4" ,
	"M":"5", 
	"N":"5" ,
	"O":"9" ,
	"P":"1" ,
	"Q":"2" ,
	"R":"6" ,
	"S":"2" ,
	"T":"3" ,
	"U":"9" ,
	"V":"1" ,
	"W":"9" ,
	"X":"2" ,
	"Y":"9",
 	"Z":"2"}
 
def soundex(source):
	"convert string to soundex eqvuivalent"
	
	#soundex requirements:
	#source string must be at least 1 charcter
	#and must consist entirely of letters
	allChars = string.uppercase + string.lowercase
	if not re.search ('^[%s]+$' % allChars, source):
		return "0000"
		
	
	#soundex algorithm
	# 1.make first character uppercase
	source = source[0].upper() + source[1:]
	
	# 2.translate all other characters to soundex digits
	digits = source[0]
	for s in source [1:]:
		s = s.upper()
		digits += charToSoundex[s]
		
	# 3.remove consecutive duplicates
	digits2 = digits
	for d in digits[1:]:
		if digits2[-1] != d:
			digits2 += d
			
	# 4. remove all "9"s
	digits3 = re.sub ('9', '', digits2)
	
	# 5. pad end with "0"s to 4 characters
	while len(digits3) < 4:
		digits3 += "0"#
		
	# 6.return first 4 characters
	return digits3[:4]
	
if __name__ == '__main__':
	from timeit import Timer
	names = ('Woo', 'Pilgrim', 'Flingjingwalker')
	for name in names:
		statement = "soundex('%s')" % name
		t = Timer (statement, "from __main__ import soundex")
		print name.ljust(15), soundex (name), min (t.repeat())
#		print soundex (name)
	
		

