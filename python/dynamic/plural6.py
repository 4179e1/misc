import re

def rules (language):
	for line in file ('rules.%s' % language):
		pattern, search, replace = line.split()
		yield lambda word: re.search (pattern, word) and re.sub (search, replace, word)

def plural (noun, language='en'):
	for applyRule in rules (language):
		result = applyRule (noun)
		if result: return result
