from flask import Flask, jsonify, abort, make_response, url_for, redirect, request, g
import inspect
import leveldb
import json

app = Flask(__name__)
app.debug = True

PRESETS_DB = "./presets.db"
ZONES_DB = "./zones.db"

def get_db (dbpath):
	if not hasattr (g, 'db'):
		g.db = {}
	if dbpath not in g.db:
		g.db[dbpath] = leveldb.LevelDB (dbpath) 
	return g.db[dbpath]

@app.errorhandler (404)
def not_found (error):
	return make_response (jsonify ({'error': 'Not Found'}), 404)

@app.errorhandler (400)
def bad_request (error):
	return make_response (jsonify ({'error': 'Bad Request'}), 400)

@app.errorhandler (501)
def not_implemented (error):
	return make_response (jsonify ({'error': 'Not Implemented'}), 501)

@app.route ('/')
def index ():
	api_list = {
		"api" :
		[
			{
				"name" : "V1 SVC",
				"desc": "Version 1 service",
				"uri" : url_for ("v1_svc", _external=True),
			},
		]
	}

	return jsonify (api_list)
@app.route ('/api/v1/svc')
def v1_svc ():
	api_list = {
		"api" :
		[
			{
				"name" : "Presets",
				"desc": "Presets of different collections",
				"uri" : url_for ("cbs_svc", svc="presets", _external=True),
			},
			{
				"name" : "Zones",
				"desc": "Availe Zones",
				"uri" : url_for ("cbs_svc", svc="zones", _external=True),
			},
		]
	}

	return jsonify (api_list)

@app.route ('/api/v1/svc/<svc>')
def cbs_svc(svc):
	if svc == 'presets':
		api_list = {
			"api" :
			[
				{
					"method": "GET",
					"desc": "List Presets",
					"uri": url_for ('presets_list', _external=True),
				},
				{
					"method": "POST",
					"desc": "Add Preset",
					"uri": url_for ('presets_add', _external=True),
				},
				{
					"method": "GET, POST",
					"desc": "List a Preset",
					"uri": url_for ('preset_list', name="EXAMPLE_PRESET", _external=True),
				},
				{
					"method": "DELETE",
					"desc": "Delete Presets",
					"uri": url_for ('presets_delete', name="EXAMPLE_PRESET", _external=True),
				},
			]
		}
	elif svc == 'zones':
		api_list = {
			"api" :
			[
				{
					"method": "GET",
					"desc": "List Zones",
					"uri": url_for ('zones_list', _external=True),
				},
				{
					"method": "POST",
					"desc": "Add Zones",
					"uri": url_for ('zones_add', _external=True),
				},
				{
					"method": "GET, POST",
					"desc": "Delete Zone",
					"uri": url_for ('zone_list', name="EXAMPLE_ZONE", _external=True),
				},
				{
					"method": "DELETE",
					"desc": "Delete Zones",
					"uri": url_for ('zones_delete', name="EXAMPLE_ZONE", _external=True),
				},
			]
		}
	else:
		abort (404)

	return jsonify (api_list)


def test_caller ():
	return jsonify (test_caller())	

@app.route ('/api/v1/presets', methods=['GET'])
def presets_list ():
	items = {}
	db = get_db (PRESETS_DB)

	for k, v in db.RangeIter():
		items[k] = json.loads (v)

	return jsonify (items)

@app.route ('/api/v1/presets', methods=['POST'])
def presets_add ():
	if not request.json:
		abort (400)

	db = get_db (PRESETS_DB)

	data = request.json

	for k, v in data.items():
		db.Put (k, json.dumps(v))

	return jsonify ({"result": 0})

@app.route ('/api/v1/presets/<name>', methods=['GET', 'POST'])
def preset_list (name):
	return jsonify (test_caller())	

@app.route ('/api/v1/presets/<name>', methods=['DELETE'])
def presets_delete (name):
	return jsonify (test_caller())	

@app.route ('/api/v1/zones', methods=['GET'])
def zones_list ():
	return jsonify (test_caller())	

@app.route ('/api/v1/zones', methods=['POST'])
def zones_add ():
	return jsonify (test_caller())

@app.route ('/api/v1/zones/<name>', methods=['GET', 'POST'])
def zone_list (name):
	return jsonify (test_caller())

@app.route ('/api/v1/zones/<name>', methods=['DELETE'])
def zones_delete (name):
	return jsonify (test_caller())

if __name__ == "__main__":
	app.run (host="0.0.0.0", port=5000)
