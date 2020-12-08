from bson.son import SON

from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']

db.inventory.insert_many([{"_id": 1, "item": None}, {"_id": 2}])

print (">>> is null, or missing")
for c in db.inventory.find({"item": None}):
    print (c)

print (">>> is null, BSON Type Null (that's number 10)")
for c in db.inventory.find({"item": {"$type": 10}}):
    print (c)

print (">>> do not exists")
for c in db.inventory.find({"item": {"$exists": False}}):
    print (c)

for col in db.collection_names():
    db[col].drop()