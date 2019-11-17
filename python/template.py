import fileinput, re

field_pat = re.compile(r'\[(.+?)\]')
scope={}

def replacement(match):
    code = match.group(1)
    try:
        return str(eval(code, scope))
    except SyntaxError:
        exec (code, scope)
        return ''

lines = []
for line in fileinput.input():
    lines.append(line)
text = ''.join (lines)

print (field_pat.sub (replacement, text).strip('\r\n'))
