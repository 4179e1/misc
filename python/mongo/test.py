import pymongo
from pymongo import MongoClient
import datetime
import pprint
from bson.objectid import ObjectId

client = MongoClient('mongodb://localhost:27017/')
db = client.test_database
collection = db.test_collection

post = {"author": "Mike",
        "text": "My first blog post!",
        "tags": ["mongodb", "python", "pymongo"],
        "date": datetime.datetime.utcnow()}

posts = db.posts
post_id = posts.insert_one(post).inserted_id
print (post_id)

print (db.collection_names(include_system_collections=False))

pprint.pprint(posts.find_one())
pprint.pprint(posts.find_one({"author": "Eliot"}))
pprint.pprint(posts.find_one({"_id": post_id}))

# Note that an ObjectId is not the same as its string representation:
post_id_as_str = str(post_id)
posts.find_one({"_id": post_id_as_str}) # No result

def get(post_id):
    # Convert from string to ObjectId:
    document = client.db.collection.find_one({'_id': ObjectId(post_id)})

pprint.pprint (get(post_id_as_str))
