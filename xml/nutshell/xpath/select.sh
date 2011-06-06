a=(
#		"/people/person/name/first_name"
#		"/people/person/name/first_name/text()"
#		"name"
		# the same as "/descendant::name"
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
#		"/people/person[@born < 1950]/name[first_name='Alan']"
#		"/child::people/child::person[attribute::born < 1950]/child::name[child::first_name='Alan']"
#		"/descendant::person/child::name/following-sibling::*"
#		"//name[starts-with(last_name, 'T')]"
#		"count(//person)"
#		"id('p342 p4567')"
#		"id('p342')/name"
#		"//homepage/@xlink:href)"
#		"local-name(//homepage/@xlink:href)"
#		"namespace-uri(//homepage/@xlink:href)"
#		"name(//homepage/@xlink:href)"
#		"//first_name[contains(., 'ar')]"
		# don't actully work, but illustrate
		# "substring-before ('MM/DD/YYYY', '/')"
		# "substring-after ('MM/DD/YYYY', '/')"
		# "substring-before (substring-after ('MM/DD/YYYY', '/'), '/')"
		# "substring ('MM/DD/YYYY', 4, 2)	# DD
		# "substring ('MM/DD/YYYY', 7)		# YYYY

#		"string-length(//name[first_name='Alan'])"
		"string(//name[position( )=1])"
		"normalize-space (string(//name[position( )=1]))"
		
   )

for i in "${a[@]}";do
	echo "============== Selecting '$i' ================="
	xpath person.xml "$i"
	echo "====================== DONE ===================="
done
