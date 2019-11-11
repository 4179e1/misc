#!/usr/bin/env python
# https://docs.mongodb.com/manual/tutorial/getting-started/

import pymongo
from pymongo import MongoClient
import datetime
import pprint
from bson.objectid import ObjectId
from bson.son import SON
import sys

# connecting to server
client = MongoClient('mongodb://localhost:27017/')

# database
db = client.test_database

inventory = db.inventory
db.inventory.insert_many([
   # MongoDB adds the _id field with an ObjectId if _id is not present
   { "item": "journal", "qty": 25, "status": "A",
       "size": { "h": 14, "w": 21, "uom": "cm" }, "tags": [ "blank", "red" ] },
   { "item": "notebook", "qty": 50, "status": "A",
       "size": { "h": 8.5, "w": 11, "uom": "in" }, "tags": [ "red", "blank" ] },
   { "item": "paper", "qty": 100, "status": "D",
       "size": { "h": 8.5, "w": 11, "uom": "in" }, "tags": [ "red", "blank", "plain" ] },
   { "item": "planner", "qty": 75, "status": "D",
       "size": { "h": 22.85, "w": 30, "uom": "cm" }, "tags": [ "blank", "red" ] },
   { "item": "postcard", "qty": 45, "status": "A",
       "size": { "h": 10, "w": 15.25, "uom": "cm" }, "tags": [ "blue" ] }
])

cursor = db.inventory.find (
    # SON for ordered dict
    #{"size": SON([("h", 14), ("uom", "cm"), ("w", 21)])} #
    {"size": {"h": 14, "w": 21, "uom": "cm"}}
)
for x in cursor:
    pprint.pprint (x)

print ('> match a filed in embedded document')
cursor = db.inventory.find({"size.uom": "in"})
for x in cursor:
    pprint.pprint (x)

print ('> match an element in an array')
cursor = db.inventory.find({"tags": "red"})
for x in cursor:
    pprint.pprint (x)

print ('> match an array exactly')
cursor = db.inventory.find({"tags": ["red", "blank"]})
for x in cursor:
    pprint.pprint (x)

print ('> match array - or')
cursor = db.inventory.find({"tags": {"$all": ["red", "blank"]}})
for x in cursor:
    pprint.pprint (x)

print ('> match array - multi criteria')
cursor = db.inventory.find({"qty": {"$gt": 30, "$lt": 70 }})
for x in cursor:
    pprint.pprint (x)


print ('> query by multi condition')
for x in db.inventory.find ({"item": "journal", "qty": 25}): 
    pprint.pprint (x)


# remove all
db.inventory.remove ({})