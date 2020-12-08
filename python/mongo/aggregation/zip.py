# https://docs.mongodb.com/manual/reference/operator/aggregation/redact/#examples
import pprint
import json
from bson.son import SON
from bson.code import Code
from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']


db.things.insert_many([
    {
        "_id": "10280",
        "city": "NEW YORK",
        "state": "NY",
        "pop": 5574,
        "loc": [
            -74.016323,
            40.710537
        ]
    },
    {
        "_id": "10281",
        "city": "bbb",
        "state": "NJ",
        "pop": 5574,
        "loc": [
            -74.016323,
            40.710537
        ]
    },
    {
        "_id": "10800",
        "city": "aaa",
        "state": "NJ",
        "pop": 1234,
        "loc": [
            74.016323,
            40.710537
        ]
    },
])

print(">>> Return States with Populations above 5k")
res = db.things.aggregate(
    [
        {"$group": {"_id": "$state", "totalPop": {"$sum": "$pop"}}},
        {"$match": {"totalPop": {"$gte": 5000}}}
    ]
)
for r in res:
    print(json.dumps(r, indent=2))

print(">>> Return Average City Population by State")
res = db.things.aggregate(
    [
        {"$group": {"_id": {"state": "$state", "city": "$city"}, "pop": {"$sum": "$pop"}}},
        {"$group": {"_id": "$_id.state", "avgCityPop": {"$avg": "$pop"}}}
    ]
)
for r in res:
    print(json.dumps(r, indent=2))

print(">>> Return Largest and Smallest Cities by State")
res = db.things.aggregate([
    {
        "$group":
        {
            "_id": {"state": "$state", "city": "$city"},
            "pop": {"$sum": "$pop"}
        }
    },
    {"$sort": {"pop": 1}},
    {"$group":
        {
            "_id": "$_id.state",
            "biggestCity":  {"$last": "$_id.city"},
            "biggestPop":   {"$last": "$pop"},
            "smallestCity": {"$first": "$_id.city"},
            "smallestPop":  {"$first": "$pop"}
        }
     },
    # the following $project is optional, and
    # modifies the output format.
    {"$project":
     {"_id": 0,
      "state": "$_id",
      "biggestCity":  {"name": "$biggestCity",  "pop": "$biggestPop"},
      "smallestCity": {"name": "$smallestCity", "pop": "$smallestPop"}
      }
     }
]
)
for r in res:
    print(json.dumps(r, indent=2))

for col in db.collection_names():
    db[col].drop()
