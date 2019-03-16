# https://docs.mongodb.com/manual/reference/operator/aggregation/redact/#examples
import pprint
import json
from bson.son import SON
from bson.code import Code
from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']


db = MongoClient().aggregation_example
result = db.things.insert_one({
    "_id": 1,
    "title": "123 Department Report",
    "tags": ["G", "STLW"],
    "year": 2014,
    "subsections": [
        {
            "subtitle": "Section 1: Overview",
            "tags": ["SI", "G"],
            "content":  "Section 1: This is the content of section 1."
        },
        {
            "subtitle": "Section 2: Analysis",
            "tags": ["STLW"],
            "content": "Section 2: This is the content of section 2."
        },
        {
            "subtitle": "Section 3: Budgeting",
            "tags": ["TK"],
            "content": {
                "text": "Section 3: This is the content of section3.",
                "tags": ["HCS"]
            }
        }
    ]
})

userAccess = ["STLW", "G"]


res = db.things.aggregate(
    [
        {'$match': {'year': 2014}},
        {
            '$redact': {
                '$cond': [{'$gt': [{'$size': {'$setIntersection': ["$tags", userAccess]}}, 0]}, "$$DESCEND", "$$PRUNE"]
            }
        }
    ]
)

for r in res:
    print(json.dumps(r, indent=2))


db.accounts.insert_one(
    {
        "_id": 1,
        "level": 1,
        "acct_id": "xyz123",
        "cc": {
            "level": 5,
            "type": "yy",
            "num": 000000000000,
            # "exp_date": ISODate("2015-11-01T00:00:00.000Z"),
            "billing_addr": {
                "level": 5,
                "addr1": "123 ABC Street",
                "city": "Some City"
            },
            "shipping_addr": [
                {
                    "level": 3,
                    "addr1": "987 XYZ Ave",
                    "city": "Some City"
                },
                {
                    "level": 3,
                    "addr1": "PO Box 0123",
                    "city": "Some City"
                }
            ]
        },
        "status": "A"
    }
)


res = db.accounts.aggregate(
    [
        {'$match': {"status": "A"}},
        {
            '$redact': {
                '$cond': [{'$eq': ['$level', 5]}, '$$PRUNE', '$$DESCEND']
            }
        }
    ]
)

for r in res:
    print(json.dumps(r, indent=2))


for col in db.collection_names():
    db[col].drop()
