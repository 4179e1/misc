define(`LQ', `changequote(<,>)`dnl'
changequote`'')dnl
define(`RQ', `changequote(<,>)dnl`
'changequote`'')dnl

define(myne, `It`'RQ()s mine!')dnl
LQ()LQ()myne''
