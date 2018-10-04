cwd=~/workspace/misc/go

if echo $GOPATH | grep -q $cwd; then
    :
else
    export GOPATH=$cwd:$GOPATH
fi
echo $GOPATH
