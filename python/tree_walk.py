import sys

tree = {
	"value": 0.1,
	"children": [
		{
			"value": 1.1,
			"children": [
				{
					"value": 2.1,
					"children": []
				},
				{
					"value": 2.2,
					"children": []
				}
			]
		},
		{
			"value": 1.2,
			"children": [
			]
		}
	]

}

def walk_recursive (node):
	# tree and leaf
	print (node['value'])
	if not node['children']:
		# leaf only
		#print (node['value'])
		return
	for child in node['children']:
		walk_recursive (child)

def walk_non_recursive (tree):
	stack = [tree]

	while stack:
		node = stack.pop ()	
		# tree and leaf
		print (node['value'])

		if not node['children']:
			#print (node['value'])
			#print (stack)
			pass
		for child in node['children']:
			stack.append (child)
		

#walk_recursive (tree)


walk_non_recursive (tree)
