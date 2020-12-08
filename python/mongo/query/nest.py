# Subdocument key order matters in a few of these examples so we have
# to use bson.son.SON instead of a Python dict.
from bson.son import SON

from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']

db.inventory.insert_many([
    {"item": "journal",
     "qty": 25,
     "size": SON([("h", 14), ("w", 21), ("uom", "cm")]),
     "status": "A"},
    {"item": "notebook",
     "qty": 50,
     "size": SON([("h", 8.5), ("w", 11), ("uom", "in")]),
     "status": "A"},
    {"item": "paper",
     "qty": 100,
     "size": SON([("h", 8.5), ("w", 11), ("uom", "in")]),
     "status": "D"},
    {"item": "planner",
     "qty": 75,
     "size": SON([("h", 22.85), ("w", 30), ("uom", "cm")]),
     "status": "D"},
    {"item": "postcard",
     "qty": 45,
     "size": SON([("h", 10), ("w", 15.25), ("uom", "cm")]),
     "status": "A"}])

print ("> exactly match by squence")
cursor = db.inventory.find (
    {"size":SON([("h", 14), ("w", 21), ("uom", "cm") ])}
)
for c in cursor:
    print (c)


print ("> match in")
for c in db.inventory.find ({"size.uom": "in"}):
    print (c)

print ("> match operator")
for c in db.inventory.find ({"size.h": {"$lt": 15}}):
    print (c)

print ("> match and")
for c in db.inventory.find ({'size.h': {'$lt': 15} , "size.uom": "in", "status": "D" }):
    print (c)