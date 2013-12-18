import re

some_text = 'alpha, beta,,,,gamma delta'
print (re.split('[, ]+', some_text))
print (re.split('[, ]+', some_text, maxsplit=2))
print (re.split('[, ]+', some_text, maxsplit=1))
