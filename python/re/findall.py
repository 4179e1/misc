import re
pat = '[a-zA-Z]+'
text = '"Hm...Err -- are you sure? " he said, sounindg insecure.'
print (re.findall(pat, text))
pat = '[.?\-", ]+'
print (re.findall(pat, text))
