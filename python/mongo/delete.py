from bson.son import SON

from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']

db.inventory.insert_many([
    {"item": "journal",
     "qty": 25,
     "size": {"h": 14, "w": 21, "uom": "cm"},
     "status": "A"},
    {"item": "notebook",
     "qty": 50,
     "size": {"h": 8.5, "w": 11, "uom": "in"},
     "status": "P"},
    {"item": "paper",
     "qty": 100,
     "size": {"h": 8.5, "w": 11, "uom": "in"},
     "status": "D"},
    {"item": "planner",
     "qty": 75,
     "size": {"h": 22.85, "w": 30, "uom": "cm"},
     "status": "D"},
    {"item": "postcard",
     "qty": 45,
     "size": {"h": 10, "w": 15.25, "uom": "cm"},
     "status": "A"}])


print (">>> delete match")
db.inventory.delete_many({"status": "A"})
for c in db.inventory.find():
    print (c)


print (">>> delete one")
db.inventory.delete_one({"status": "D"})
for c in db.inventory.find():
    print (c)


print (">>> delete all")
db.inventory.delete_many({})

for c in db.inventory.find():
    print (c)

for col in db.collection_names():
    db[col].drop()
