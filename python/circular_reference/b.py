#!/usr/bin/env python
import json

def new_tree (name):
	return {
		"name": name,
	}

def new_child_tree (parent, name):
	if 'children' not in parent:
		parent['children'] = {}	
	if name not in parent['children']:
		parent['children'][name] = new_tree (name)
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
