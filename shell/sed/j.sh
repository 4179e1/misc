NAME=iqn.2010-08.com.skybility:md1
object=/dev/md0
TID=1
sed -n '/^tid:'"$TID"'/, /^tid:/ s/^.*lun:\([[:digit:]]*\).*path:'"$object"'/\1/p'
