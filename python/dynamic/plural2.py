import re

def match_sxz (noun):
	return re.search ('[sxz]$', noun)

def apply_sxz (noun):
	return re.sub ('$', 'es', noun)

def match_h (noun):
	return re.search ('[^aeioudgkprt]h$', noun)

def apply_h (noun):
	return re.sub ('$', 'es', noun)

def match_y (noun):
	return re.search ('[^aeiou]y$', noun)

def apply_y (noun):
	return re.sub ('y$', 'ies', noun)

def match_default (noun):
	return 1

def apply_default (noun):
	return noun + 's'

rules = ((match_sxz, apply_sxz),
	 (match_h, apply_h),
	 (match_y, apply_y),
	 (match_default, apply_default)
	 )

def plural (noun):
	for matchesRule, applyRule in rules:
		if matchesRule (noun):
			return applyRule (noun)
