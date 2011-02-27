dnl recursion
define(`for', `ifelse($#, 0, ``$0'', `ifelse(eval($2<=$3), 1,
`pushdef(`$1', $2)$4`'popdef(`$1')$0(`$1', incr($2), $3, `$4')')')')dnl
for n = for(`x', 1, 5, `x, ')...
for(`x', 1, 3, `for(`x', 0, 4, `eval(5-x)') ')

dnl only 3 arguments for ifelse()
define(`foreach', `ifelse(eval($#>2), 1,
`pushdef(`$1', `$3')$2`'popdef(`$1')dnl for the line is break into 2 line
`'ifelse(eval($#>3), 1, `$0(`$1', `$2', shift(shift(shift($@))))')')')dnl
foreach(`X', `Open the X. ', `door', `window')
foreach(`X', `foreach(`Y', `Y the X. ', `Open', `Close')', `door', `window')

define(`OPER', ``$1 the $2'')dnl
foreach(`XY', `OPER(XY). ', ``Open',`window'', ``Close', `door'')

dnl dectect the last element.
define(`foreach', `ifelse(eval($#>2), 1,
`pushdef(`last_$1', eval($#==3))dnl
`'pushdef(`$1', `$3')$2`'popdef(`$1')dnl
`'ifelse(eval($#>3), 1, `$0(`$1', `$2', shift(shift(shift($@))))')')')dnl
define(`everyone', ``Tom',`Dick',`Harry'')dnl
foreach(`one', `one`'ifelse(last_one, 0, ` and ')', everyone).

define(`while', `ifelse($#, 0, ``$0'',
eval($1+0), 1, `$2`'$0($@)')')dnl
define(`POW2', 2)dnl
while(`POW2<=1000', `define(`POW2', eval(POW2*2))')dnl
POW2
