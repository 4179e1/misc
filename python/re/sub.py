import re
pat='{name}'
text = 'Dear {name}...'
print (re.sub (pat, 'Mr. Gumby', text))

emphasis_pattern = re.compile (r'''
        \*  # beginning emphasis tag -- an asterisk
        (   # beginning group for captureing phrase
        [^\*]+ # Capture every thing except asterisks
        )   # End group
        \*  # ending emphasis tag
        ''', re.VERBOSE)
print (re.sub (emphasis_pattern, r'<em>\1</em>', 'Hello, *world*!'))


emphasis_pattern = r'\*\*(.+?)\*\*'
print (re.sub (emphasis_pattern, r'<em>\1</em>', '**This** is **it**!'))
