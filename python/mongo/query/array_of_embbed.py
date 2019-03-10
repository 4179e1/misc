from bson.son import SON

from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']

db.inventory.insert_many([
    {"item": "journal",
     "instock": [
         SON([("warehouse", "A"), ("qty", 5)]),
         SON([("warehouse", "C"), ("qty", 15)])]},
    {"item": "notebook",
     "instock": [
         SON([("warehouse", "C"), ("qty", 5)])]},
    {"item": "paper",
     "instock": [
         SON([("warehouse", "A"), ("qty", 60)]),
         SON([("warehouse", "B"), ("qty", 15)])]},
    {"item": "planner",
     "instock": [
         SON([("warehouse", "A"), ("qty", 40)]),
         SON([("warehouse", "B"), ("qty", 5)])]},
    {"item": "postcard",
     "instock": [
         SON([("warehouse", "B"), ("qty", 15)]),
         SON([("warehouse", "C"), ("qty", 35)])]}])


print (">>> instack exactly match")
for c in db.inventory.find(
    {"instock": SON([("warehouse", "A"), ("qty", 5)])}):
    print (c)

print (">>>  instock array has at least one embedded document that contains the field qty whose value is less than or equal to 20:")
for c in db.inventory.find({'instock.qty': {"$lte": 20}}):
    print (c)

print (">>> index")
for c in db.inventory.find({'instock.0.qty': {"$lte": 20}}):
    print (c)

print (">>> instock array has at least one embedded document that contains both the field qty equal to 6 and the field warehouse equal to A:")
for c in db.inventory.find(
    {"instock": {"$elemMatch": {"qty": 5, "warehouse": "A"}}}):
    print (c)

print (">>> instock array has at least one embedded document that contains the field qty that is greater than 10 and less than or equal to 20:")
for c in db.inventory.find(
    {"instock": {"$elemMatch": {"qty": {"$gt": 10, "$lte": 20}}}}):
    print (c)

print (">>> instock array has the qty field greater than 10 and any document (but not necessarily the same embedded document) in the array has the qty field less than or equal to 20:")
for c in db.inventory.find({"instock.qty": {"$gt": 10, "$lte": 20}}):
    print (c)

print (">>> instock array has at least one embedded document that contains the field qty equal to 5 and at least one embedded document (but not necessarily the same embedded document) that contains the field warehouse equal to A:")
for c in db.inventory.find(
    {"instock.qty": 5, "instock.warehouse": "A"}):
    print (c)

for col in db.collection_names():
    db[col].drop()