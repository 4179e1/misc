define(`sigma', `ifelse(eval($1<=1), 1, $1, `eval($1+sigma(decr($1)))')')dnl
sigma(10)
sigma(1000)
