#!/usr/bin/env python
import json

def new_tree (name, children={}):
	return {
		"name": name,
		"children": children,
	}
''' 
So where the hell comes the circular reference ?!
the default parameter children were something like a static variable,
it only have one copy through all the life cycle
We were essentially writing:

children = {}

a = {
	"name": "a",
	"children": children,
}

b = {
	"name": "b",
	"children": children,
}

a['children']['b'] = b
'''
def new_child_tree (parent, name, children={}):
	#print ("id of children %ld"  % id(children))
	if 'children' not in parent:
		parent['children'] = {}	
	if name not in parent['children']:
		parent['children'][name] = new_tree (name, children)
	return parent['children'][name]

def build_tree (root, a):
	parent = root
	for x in a:
		parent = new_child_tree (parent, x)

if __name__ == "__main__":
	root = new_tree ("root")
	a1 = ["a", "b", "c"]
	a2 = ["a", "b", "e"]

	build_tree (root, a1)
	build_tree (root, a2)

	print (json.dumps (root, indent=2))
