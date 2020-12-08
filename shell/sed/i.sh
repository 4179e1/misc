NAME="iqn.2010-08.com.skybility:iscsi"
LUN_ID=0
object=/dev/lvmdatas/iscsi
TYPE=fileio

sed -i '/^Target '"$NAME"'$/ a\	Lun '"$LUN_ID"' Path='"$object"',Type='"$TYPE" i.txt
