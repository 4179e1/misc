from bson.son import SON

from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']

db.inventory.insert_many([
    {"item": "journal",
     "status": "A",
     "size": {"h": 14, "w": 21, "uom": "cm"},
     "instock": [{"warehouse": "A", "qty": 5}]},
    {"item": "notebook",
     "status": "A",
     "size": {"h": 8.5, "w": 11, "uom": "in"},
     "instock": [{"warehouse": "C", "qty": 5}]},
    {"item": "paper",
     "status": "D",
     "size": {"h": 8.5, "w": 11, "uom": "in"},
     "instock": [{"warehouse": "A", "qty": 60}]},
    {"item": "planner",
     "status": "D",
     "size": {"h": 22.85, "w": 30, "uom": "cm"},
     "instock": [{"warehouse": "A", "qty": 40}]},
    {"item": "postcard",
     "status": "A",
     "size": {"h": 10, "w": 15.25, "uom": "cm"},
     "instock": [
         {"warehouse": "B", "qty": 15},
         {"warehouse": "C", "qty": 35}]}])


print (">>> projection")
for c in db.inventory.find(
    {"status": "A"}, {"item": 1, "status": 1}):
    print (c)

print (">>> uppres _id")
for c in db.inventory.find(
    {"status": "A"}, {"item": 1, "status": 1, "_id": 0}):
    print (c)

print (">>> exclude")
for c in db.inventory.find(
    {"status": "A"}, {"status": 0, "instock": 0}):
    print (c)

print (">>> projection size.uom")
for c in db.inventory.find(
    {"status": "A"}, {"item": 1, "status": 1, "size.uom": 1}):
    print (c)

print (">>> suppress size.uom")
for c in db.inventory.find({"status": "A"}, {"size.uom": 0}):
    print (c)


print (">>> projection in array")
for c in db.inventory.find(
    {"status": "A"}, {"item": 1, "status": 1, "instock.qty": 1}):
    print (c)

print (">>> array slice")
for c in db.inventory.find(
    {"status": "A"},
    {"item": 1, "status": 1, "instock": {"$slice": -1}}):
    print (c)

for col in db.collection_names():
    db[col].drop()