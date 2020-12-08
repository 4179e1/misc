#try $0 "ls | grep com"
eval "$@" >longfile 2>&1 &
