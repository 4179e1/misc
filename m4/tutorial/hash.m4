define(`my var', `a strange one')dnl
my var is defn(`my var').

define(`_set', `define(`$1[$2]', `$3')')dnl
define(`_get', `defn(`$1[$2]')')dnl
_set(`myarray', 1, `alpha')
_get(`myarray', 1)
_set(`myarray', `alpha', `omega')
_get(`myarray', _get(`myarray', 1))
defn(`myarray[alpha]')
