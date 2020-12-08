
import string, re

allChars = string.uppercase + string.lowercase
charToSoundexTrans =  string.maketrans(allChars, "91239129922455912623919292"*2)
isOnlyChars = re.compile('^[A-Za-z]+$')

#charToSoundex = {
#	"A":"9",
#	"B":"1",
#	"C":"2",
#	"D":"3", 
#	"E":"9" ,
#	"F":"1", 
#	"G":"2" ,
#	"H":"9" ,
#	"I":"9" ,
#	"J":"2" ,
#	"K":"2" ,
#	"L":"4" ,
#	"M":"5", 
#	"N":"5" ,
#	"O":"9" ,
#	"P":"1" ,
#	"Q":"2" ,
#	"R":"6" ,
#	"S":"2" ,
#	"T":"3" ,
#	"U":"9" ,
#	"V":"1" ,
#	"W":"9" ,
#	"X":"2" ,
#	"Y":"9",
# 	"Z":"2"}

 
def soundex(source):
	"convert string to soundex eqvuivalent"
	
	#soundex requirements:
	#source string must be at least 1 charcter
	#and must consist entirely of letters
############################################################################
#	allChars = string.uppercase + string.lowercase
#	if not re.search ('^[%s]+$' % allChars, source):
	if not isOnlyChars.search(source):
		return "0000"

# Woo             W000 9.08934497833
# Pilgrim         P426 13.0586299896
# Flingjingwalker F452 19.1422040462
		
############################################################################
#	#soundex algorithm
#	# 1.make first character uppercase
#	source = source[0].upper() + source[1:]
#	
#	# 2.translate all other characters to soundex digits
#	digits = source[0]
#	for s in source [1:]:
#		s = s.upper()
#		digits += charToSoundex[s]

	digits = source[0].upper() + source[1:].translate (charToSoundexTrans)

# Woo             W000 7.96419596672
# Pilgrim         P426 10.497628212
# Flingjingwalker F452 13.3242239952
	
############################################################################
	# 3.remove consecutive duplicates
	digits2 = digits
	for d in digits[1:]:
		if digits2[-1] != d:
			digits2 += d
			
############################################################################
#	# 4. remove all "9"s
#	digits3 = re.sub ('9', '', digits2)
#	
#	# 5. pad end with "0"s to 4 characters
#	while len(digits3) < 4:
#		digits3 += '0'
#		
#	# 6.return first 4 characters
#	return digits3[:4]

	return (digits2.replace('9', '') + '000')[:4]

# Woo             W000 4.1453909874
# Pilgrim         P426 5.69330000877
# Flingjingwalker F452 7.58190608025
	
if __name__ == '__main__':
	from timeit import Timer
	names = ('Woo', 'Pilgrim', 'Flingjingwalker')
	for name in names:
		statement = "soundex('%s')" % name
		t = Timer (statement, "from __main__ import soundex")
		print name.ljust(15), soundex (name), min (t.repeat())
#		print soundex(name)	

