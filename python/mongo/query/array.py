from bson.son import SON

from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']

db.inventory.insert_many([
    {"item": "journal",
     "qty": 25,
     "tags": ["blank", "red"],
     "dim_cm": [14, 21]},
    {"item": "notebook",
     "qty": 50,
     "tags": ["red", "blank"],
     "dim_cm": [14, 21]},
    {"item": "paper",
     "qty": 100,
     "tags": ["red", "blank", "plain"],
     "dim_cm": [14, 21]},
    {"item": "planner",
     "qty": 75,
     "tags": ["blank", "red"],
     "dim_cm": [22.85, 30]},
    {"item": "postcard",
     "qty": 45,
     "tags": ["blue"],
     "dim_cm": [10, 15.25]}])

print (">>> exactly red and blank")
for c in db.inventory.find ({"tags": ["red", "blank"]}):
    print (c)

print (">>> both red and blank, disregard other elems or order")
for c in db.inventory.find ({"tags":  {"$all": ["red", "blank"]}}):
    print (c)

print (">>> contain red")
for c in db.inventory.find ({"tags": "red"}):
    print (c)

print (">>> at least one > 25")
for c in db.inventory.find ({"dim_cm": {"$gt": 25}}):
    print (c)


print (">>> one element can satisfy the greater than 15 condition and another element can satisfy the less than 20 condition, or a single element can satisfy both:")
for c in db.inventory.find({"dim_cm": {"$gt": 15, "$lt": 20}}):
    print (c)


print (">>> at least one element that is both greater than ($gt) 22 and less than ($lt) 30:")
for c in  db.inventory.find(
    {"dim_cm": {"$elemMatch": {"$gt": 22, "$lt": 30}}}):
    print (c)

print (">>> by index")
for c in db.inventory.find({"dim_cm.1": {"$gt": 25}}):
    print (c)

print (">>> by length")
for c in db.inventory.find({"tags": {"$size": 3}}):
    print (c)

for col in db.collection_names():
    db[col].drop()