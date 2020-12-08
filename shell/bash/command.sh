cd /
echo previous: ~-
echo current: ~+
cd - &>/dev/null

person=hatter
echo $person
echo "$person"
echo \$person
echo '$person'
echo "'$person'"
echo ~root
echo "~root"
echo '~root'
