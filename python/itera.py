strings=[
'Hello world!',
'Hello mOtO!',
]

for index, string in enumerate (strings):
    if 'Moto'.lower() in string.lower():
        strings[index]='Hello, google!'
print (strings)
