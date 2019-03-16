import pprint
from bson.son import SON
from bson.code import Code
from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']


db = MongoClient().aggregation_example
result = db.things.insert_many([{"x": 1, "tags": ["dog", "cat"]},
                                {"x": 2, "tags": ["cat"]},
                                {"x": 2, "tags": ["mouse", "cat", "dog"]},
                                {"x": 3, "tags": []}])


def pipeline():
    pipeline = [
        {"$unwind": "$tags"},
        {"$group": {"_id": "$tags", "count": {"$sum": 1}}},
        {"$sort": SON([("count", -1), ("_id", -1)])}
    ]
    import pprint
    pprint.pprint(list(db.things.aggregate(pipeline)))

    # explain
    #db.command('aggregate', 'things', pipeline=pipeline, explain=True)


def map_reduce():
    mapper = Code("""
                  function () {
                    this.tags.forEach(function(z) {
                      emit(z, 1);
                    });
                  }
                  """)

    reducer = Code("""
                   function (key, values) {
                     var total = 0;
                     for (var i = 0; i < values.length; i++) {
                       total += values[i];
                     }
                     return total;
                   }
                   """)

    result = db.things.map_reduce(mapper, reducer, "myresults")
    for doc in result.find():
        pprint.pprint(doc)


pipeline()
# map_reduce()

for col in db.collection_names():
    db[col].drop()
