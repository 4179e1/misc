define(`substr',`ifelse($#,0,``$0'',
$#,2,`substr($@,eval(len(`$1')-$2))',
`ifelse(eval($3<=0),1,,
`builtin(`substr',`$1',$2,1)`'substr(
`$1',eval($2+1),eval($3-1))')')')dnl
define(`eng', `engineering')
substr(`engineer', 0, 3)

define(`translit',`ifelse($#,0,``$0'',
len(`$1'),0,,
`builtin(`translit',substr(`$1',0,1),`$2',`$3')`'translit(
substr(`$1',1),`$2',`$3')')')dnl
translit(`alpha', ALPHA, ALPHA_UPR)
