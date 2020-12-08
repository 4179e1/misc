#!/usr/bin/env python

from flask import Flask, jsonify, abort, make_response, request, url_for
from flask_httpauth import HTTPBasicAuth

app = Flask(__name__)

auth = HTTPBasicAuth()
@auth.get_password
def get_password(username):
		if username == 'root':
			return 'root'
		return None

@auth.error_handler
def unauthorized():
	return make_response (jsonify({'error': 'Unauthorized access'}), 401)

@app.route ('/')
def index():
	return "Hello, world!"

@app.errorhandler (404)
def not_found (error):
	return make_response (jsonify({'error': 'Not found'}), 404)

@app.errorhandler (400)
def bad_request (error):
	return make_response (jsonify({'error': 'Invalid request'}), 400)

tasks = [
	{
		'id' : 1,
		'title' : u'Buy groceries',
		'description' : u'Milk, Cheese, Pizza, Fruit, Tylenol',
		'done': False
	},
	{
		'id' : 2,
		'title' : u'Learn Python',
		'description': u'Need to find a good Python tutorial on the webe',
		'done' : False
	}
]

def make_public_task (task):
	new_task = {}
	for field in task:
		if field == 'id':
			new_task['uri'] = url_for ('get_task', task_id=task['id'], _external=True)
		else:
			new_task[field] = task[field]
	return new_task

# curl -u root:root -i http://localhost:5000/todo/api/v1/tasks
@app.route ('/todo/api/v1/tasks', methods=['GET'])
@auth.login_required
def get_tasks():
	return jsonify ({'tasks' : map (make_public_task, tasks)})
# curl -i http://localhost:5000/todo/api/v1/tasks/1
@app.route ('/todo/api/v1/tasks/<int:task_id>', methods=['GET'])
def get_task(task_id):
	task = filter (lambda t: t['id'] == task_id, tasks)
	if len (task) == 0:
		abort (404)
	return jsonify ({'task': task[0]})

# curl -i -H "Content-Type: application/json" -X POST -d '{"title":"Read a book"}' http://localhost:5000/todo/api/v/tasks
@app.route ('/todo/api/v1/tasks', methods=['POST'])
def create_task():
	if not request.json or not 'title' in request.json:
		abort (400)
	task = {
		'id' : tasks[-1]['id'] + 1,
		'title': request.json['title'],
		'description': request.json.get ('description', ""),
		'done' : False
	}
	tasks.append (task)
	return jsonify ({'task': task}), 201

# curl -i -H "Content-Type: application/json" -X PUT -d '{"done":true}' http://localhost:5000/todo/api/v1/tasks/2
@app.route ('/todo/api/v1/tasks/<int:task_id>', methods=['PUT'])
def update_task (task_id):
	task = filter (lambda t: t['id'] == task_id, tasks)
	if len(task) == 0:
		abort (404)
	if not request.json:
		abort (400)
	if 'title' in request.json and type (request.json['title']) != unicode:
		abort (400)
	if 'description' in request.json and type (request.json['description']) is not unicode:
		abort (400)
	if 'done' in request.json and type (request.json['done']) is not bool:
		abort (400)
	task[0]['title'] = request.json.get ('title', task[0]['title'])
	task[0]['description'] = request.json.get ('description', task[0]['description'])
	task[0]['done'] = request.json.get ('done', task[0]['done'])
	
	return jsonify ({'task' : task[0]})

# curl -i -X DELETE http://localhost:5000/todo/api/v1/tasks/2
@app.route ('/todo/api/v1/tasks/<int:task_id>', methods=['DELETE'])
def delete_task (task_id):
	task = filter (lambda t: t['id'] == task_id, tasks)
	if len (task) == 0:
		abort (404)
	tasks.remove (task[0])
	return jsonify ({'result': True})

if __name__ == "__main__":
	app.run (debug=True)
