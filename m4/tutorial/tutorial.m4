define(AUTHOR, W. Shakespeare)dnl
`AUTHOR' is AUTHOR
`#' AUTHOR

define(newline, `line
break')dnl
a newline here

`AUTHOR
' is AUTHOR''

define(PARENS, ())dnl
backets: PARENS

define(LPAREN, `(')dnl
define(RPAREN, `)')dnl
LPAREN backeted RPAREN

define(LEFT, [)dnl
LEFT
define(LEFT, {)dnl
LEFT
[

define(`LEFT', `[')dnl
LEFT
define(`LEFT', `{')dnl
LEFT

define(`RIGHT', `]')dnl
undefine(RIGHT)dnl
RIGHT
undefine(`RIGHT')dnl
RIGHT

define(`Version2', A – 1 )dnl
99Version2:Version2_   Version22
Version2(arg1, arg2) Version2 (junk) garbage(trash)Version2()

define(`definenum', `define(`num', `99')')dnl
num
definenum num

define(`definenum', define(`num', `99'))dnl
num
definenum

define(`definedefineX', `define(`defineX', `define(`X', `xxx')')')dnl
dnl unexpended
defineX X
dnl defineddefineX => `define(`defineX', `define(`X', `xxx')')'
definedefineX X
dnl defineX => `define(`X', `xxx')'
defineX X

define(`stmt', ``define(`Y', `yyy')'')dnl
stmt
Y

define(`plus', `+')dnl
plusplus
plus()plus

define(`oper', `plus')dnl
dnl oper()oper => plusoper
oper()oper
dnl oper`'oper => plus`'oper => +`'oper => ... => ++
oper`'oper

dnl good practice
define(`oper', `plus`'')dnl
oper()oper

define(`Bye', `Bye for now')dnl
Hello.
dnl inifinte loop
dnl Bye.

define(`args', ``NAME', `Marie'')dnl
define(args)dnl =>define(`NAME', `Marie') =>
dnl => Marie
NAME

dnl => args() => `NAME', `Marie' -> NAME, Marie
args(define(`args', `Rache'))
dnl => Rache
args

define(`msg', `undefine(`msg')Secret message.')dnl
dnl => Secret message.
msg
dnl => msg
msg
