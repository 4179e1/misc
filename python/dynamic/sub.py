import re
print re.search('[abc]', 'Mark')
print re.sub ('[abc]', 'o', 'Mark')
print re.sub ('[abc]', 'o', 'rock')
print re.sub ('[abc]', 'o', 'caps')

print re.sub ('([^aeiou])y$', '\1ies', 'vacancy')
