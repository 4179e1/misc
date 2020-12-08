set -v
p=`pwd`
export GOPATH=${p%/*/*}:$GOPATH
go build
