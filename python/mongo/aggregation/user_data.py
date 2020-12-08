# https://docs.mongodb.com/manual/reference/operator/aggregation/redact/#examples
import pprint
import json
import datetime
from bson.son import SON
from bson.code import Code
from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']


db.users.insert_many([
    {
        "_id": "jane",
        "joined": datetime.datetime(2011, 3, 2),
        "likes": ["golf", "racquetball"]
    },
    {
        "_id": "joe",
        "joined": datetime.datetime(2012, 7, 2),
        "likes": ["tennis", "golf", "swimming"]
    }
])


def do_agg(pipeline):
    res = db.users.aggregate(pipeline)
    for r in res:
        print(json.dumps(r, indent=2))


print('>>> Normalize and Sort Documents')
pipeline = [
    {'$project': {'name': {"$toUpper": "$_id"}, "_id": 0}},
    {'$sort': {'name': 1}}
]
do_agg(pipeline)


print(">>> Return Usernames Ordered by Join Month")
pipeline = [
    {
        '$project': {
            'month_joined': {'$month': '$joined'},
            'name': "$_id",
            '_id': 0
        }
    },
    {'$sort': {'month_joined': 1}}
]
do_agg(pipeline)

print (">>> Return Total Number of Joins per Month")
pipeline = [
    {'$project': {'month_joined': {'$month': '$joined'}}},
    {'$group': {'_id': {'month_joined': '$month_joined'}, 'number': {'$sum': 1}}},
    {'$sort': {"_id.month_joined": 1}}

]
do_agg (pipeline)

print ('>>> Return the Five Most Common “Likes”')
pipeline = [
    {'$unwind': '$likes'},
    {'$group': {'_id': "$likes", 'number': {'$sum':1}}},
    {'$sort': {'number': -1}},
    {'$limit': 5}
]
do_agg (pipeline)

for col in db.collection_names():
    db[col].drop()
