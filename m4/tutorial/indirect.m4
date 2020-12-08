indir(`define', `SIZE', 78)dnl
SIZE
indir(`SIZE')

indir(`define(`SIZE')', 67)
indir(`SIZE', indir(`define', `SIZE', 53))
indir(`SIZE', indir(`undefine', `SIZE'))

define(do, $1($2, $3, $3, $5))dnl
do(`define', ``x'', 4)
x
