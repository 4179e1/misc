vm_mac=00:16:3e:0a:91:6b
sed '/^vif[ 	]*=.*/ s/\(.*\)mac=.*:..\(.*$\)/\1mac='"$vm_mac"'\2/' g.txt
