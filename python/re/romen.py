import re
# thoundsand
pattern= '^M?M?M?$'
print re.search (pattern, 'M')
print re.search (pattern, 'MM')
print re.search (pattern, 'MMM')
print re.search (pattern, 'MMMM')
print re.search (pattern, '')

pattern= '^M?M?M?(CM|CD|D?C?C?C?)$'
print re.search (pattern, 'MCM')
print re.search (pattern, 'MD')
print re.search (pattern, 'MMMCCC')
print re.search (pattern, 'MCMC')
print re.search (pattern, '')

pattern= '^M?M?M?(CM|CD|D?C?C?C?)(XC|XL|L?X?X?X?)$'
print re.search (pattern, 'MCMXL')
print re.search (pattern, 'MCML')
print re.search (pattern, 'MCMLX')
print re.search (pattern, 'MCMLXXX')
print re.search (pattern, 'MCMLXXXX')

pattern= '^M?M?M?(CM|CD|D?C?C?C?)(XC|XL|L?X?X?X?)|(IX|IV|V?I?I?I?)$'

pattern = '^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$'
print re.search (pattern, 'MDLV').groups()
print re.search (pattern, 'MMDCLXVI')
print re.search (pattern, 'MMMDCCCLXXXVIII')
print re.search (pattern, 'I')
