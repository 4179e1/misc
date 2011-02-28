define(`strlen', `len')dnl
strlen(`hello')

define(`strlen', `len($@)')dnl
strlen(`hello')

define(`strlen', `len($@)')undefine(`len')dnl
strlen(`hello')

define(`rename', `define(`$2', defn(`$1'))undefine(`$1')')dnl
rename(`define', `create')dnl
create(`vehicle', `truck')dnl
vehicle
define(`fuel', `diesel')
fuel

create a macro
create(`new', `create($@)')dnl
new(`wheels', 6)dnl
new wheels
