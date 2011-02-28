define(`ABC', `abc')dnl
dumpdef(`ABC')dnl
defn(`ABC')dnl

errprint(`this message goes to standard error(stderr)')dnl

debugmode(V)
define(`ABC', `abc')dnl
debugmode`'dnl
