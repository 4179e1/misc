a=(
#		"/people/person/name/first_name"
#		"/people/person/name/first_name/text()"
#		"name"
#		"//name"
#		"//@id"
#		"//person/@id"
#		"//@id/.."
#		"//middle_initial/../first_name"
		# Predicates
#		"//profession[.='physicist']"
#		"//person[profession='mathematician']"
#		"//person[@id='p4567']"
#		"//person[@born<=1920 and @born>=1910]"
#		"//name[first_name='Richard' or first_name='Dick']"
		# select the 2nd node"
#		"//person[2]"
		# select the node have a 'middle_initial' child element
#		"//name[middle_initial]"
		"/people/person[@born < 1950]/name[first_name='Alan']"
   )

for i in "${a[@]}";do
	echo "============== Selecting '$i' ================="
	xpath person.xml "$i"
	echo "====================== DONE ===================="
done
