import fileinfo
f = fileinfo.FileInfo ("/Users/lyre/heroes4/01 The Preserve.mp3")
print f.__class__
print f.__doc__
print f

mp3file = fileinfo.MP3FileInfo()
print mp3file
mp3file["name"] = "/Users/lyre/heroes4/01 The Preserve.mp3"
print mp3file
mp3file["name"] = "/Users/lyre/heroes4/02 The Last Battle.mp3"
print mp3file
