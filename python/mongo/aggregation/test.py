from bson.son import SON
from bson.json_util import dumps
from bson.code import Code

from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']


result = db.things.insert_many([{"x": 1, "tags": ["dog", "cat"]},
                                {"x": 2, "tags": ["cat"]},
                                {"x": 2, "tags": ["mouse", "cat", "dog"]},
                                {"x": 3, "tags": []}])


# method 1 - pipeline
pipeline = [
        {"$unwind": "$tags"},
        {"$group": {"_id": "$tags", "count": {"$sum": 1}}},
        {"$sort": SON([("count", -1), ("_id", -1)])}
    ]

r = db.things.aggregate (pipeline)
print (dumps (r, indent=2))


# the explain, which I don't understand
# r = db.command('aggregate', 'things', pipeline=pipeline, explain=True)
# print (dumps (r, indent=2))


# method 2 - map reduce
mapper = Code ("""
    function () {
        this.tags.forEach (function(z) {
            emit (z, 1);
        });
    }
""")

reducer = Code ("""
    function (key, values) {
        var total = 0;
        for (var i = 0; i < values.length; i++) {
            total += values[i];
        }
        return total;
    }
""")

result = db.things.map_reduce (mapper, reducer, "myresults")
for doc in result.find():
    print (doc)

for col in db.collection_names():
    db[col].drop()
