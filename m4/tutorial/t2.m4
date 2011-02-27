define(`def') dnl
`def' is ifdef(`def', ,not )defined.

define(`A', `abc')dnl
define(`B', `abc')dnl
define(`C', `cde')dnl
ifelse(A, B, `match', `not match')

eval(7*6)
eval(7/3+100)

define(`n', 0)dnl
n
define(`n', incr(n))dnl
n

`n' is ifelse(eval(n < 2), 1, less than , eval(n == 2), 1, greater than )2
define(`n', incr(n))dnl
n
`n' is ifelse(eval(n < 2), 1, less than , eval(n > 2), 1, greater than )2

dnl => 5
len(`hello')
dnl => ell
substr(`hello', 1, 3)
dnl => llo
substr(`hello', 2)

dnl => 2
index(`hello', `llo')
dnl => -1
index(`not it string', `xyz')

define(`ALPHA', `abcdefghijklmnopqrstuvwxyz')dnl
define(`ALPHA_UPR', `ABCDEFGHIJKLMNOPQRSTUVWXYZ')dnl
define(`ROT13', `nopqrstuvwxyzabcdefghijklm')dnl
dnl => ABC EBG13
translit(`abc ebg13', ALPHA, ALPHA_UPR)
dnl nop rot13
translit(`abc ebg13', ALPHA, ROT13)

define(`eng', `engineering')dnl
dnl => eng => enginnering
substr(`engineer', 0, 3)
dnl => eng => enginnering
translit(`rat', ALPHA, ROT13)

define(`len', `ifelse($1,,0, `eval(1+len(substr($1, 1)))')')dnl
len(abc)

define(`count', ``$0': $# args')dnl
count
count()
count(1)
count(1,)

define(`list', `$`'*: $*; $`'@: $@')dnl
list(len(`abc'), `len(`abc')')

shift(1,2, `abc', 4)
shift(one)
define(`echolast', `ifelse(eval($#<2), 1, `$1`'', `echolast(shift($@))')')dnl
echolast(one,two,three)

define(`USED', 1)dnl
define(`proc',
`pushdef(`USED',10)pushdef(`UNUSED', 20)dnl
`'`USED' = USED, `UNUSED' = UNUSED`'dnl
`'popdef(`USED', `UNUSED')')
proc
USED

define(`MYMACRO', `text')dnl
define a macro

define(`reverse', `ifelse($1,,,
`reverse(substr($1,1))`'substr($1,0,1)')')dnl
reverse drawer: reverse(`drawer')

define(`reverse', `ifelse($#,0,``$0'',$1,,,
`reverse(substr($1,1))`'substr($1,0,1)')')dnl
reverse drawer: reverse(`drawer')

substr(`drawer', 1)

dnl define(`substr',`ifelse($#,0,``$0'',
dnl $#,2,`substr($@,eval(len(`$1')-$2))',
dnl `ifelse(eval($3<=0),1,,
dnl `builtin(`substr',`$1',$2,1)`'substr(
dnl `$1',eval($2+1),eval($3-1))')')')dnl
dnl define(`eng', `engineering')
dnl substr(`engineer', 0, 3)
dnl 
dnl define(`translit',`ifelse($#,0,``$0'',
dnl len(`$1'),0,,
dnl `builtin(`translit',substr(`$1',0,1),`$2',`$3')`'translit(
dnl substr(`$1',1),`$2',`$3')')')dnl
dnl translit(`alpha', ALPHA, ALPHA_UPR)
