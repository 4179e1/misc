vm_image=IMAGE
sed -i 's/\(disk[ 	]*=[^'\'']*'\''\)[^,]*\(.*\)/\1'$vm_image'\2/' tiny
