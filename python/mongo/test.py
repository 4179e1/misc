#!/usr/bin/env python
# https://api.mongodb.com/python/current/tutorial.html

import pymongo
from pymongo import MongoClient
import datetime
import pprint
from bson.objectid import ObjectId

# connecting to server
client = MongoClient('mongodb://localhost:27017/')

# database
db = client.test_database

# collection, or 'table', not used here
collection = db.test_collection

# document, or 'record'
post = {"author": "Mike",
        "text": "My first blog post!",
        "tags": ["mongodb", "python", "pymongo"],
        "date": datetime.datetime.utcnow()}

# using collection/table posts
posts = db.posts
# insert post
post_id = posts.insert_one(post).inserted_id
print (post_id)

print (db.collection_names(include_system_collections=False))

# find the first match
pprint.pprint(posts.find_one())

print ('> empty match')
pprint.pprint(posts.find_one({"author": "Eliot"}))

print ('> the one just inserted')
pprint.pprint(posts.find_one({"_id": post_id}))

# Note that an ObjectId is not the same as its string representation:
print ('> id as string, no result')
post_id_as_str = str(post_id)
pprint.pprint (posts.find_one({"_id": post_id_as_str})) # No result

print ('> stirng to ObjectID')
pprint.pprint (posts.find_one({"_id": ObjectId(post_id_as_str)})) # No result

# bulk insert
new_posts = [{"author": "Mike",
              "text": "Another post!",
              "tags": ["bulk", "insert"],
              "date": datetime.datetime(2009, 11, 12, 11, 14)},
             {"author": "Eliot",
              "title": "MongoDB is fun",
              "text": "and pretty easy too!",
              "date": datetime.datetime(2009, 11, 10, 10, 45)}]
result = posts.insert_many(new_posts)
print (result.inserted_ids)

# iteration
# for post in posts.find():
#    pprint.pprint(post)

# iteration with limit
print ('> iteration with limit')
for post in posts.find({'author': 'Eliot'}):
    pprint.pprint(post)

# counting 
print (posts.count_documents({}))
print (posts.count_documents({"author": "Mike"}))

# range query
d = datetime.datetime(2009, 11, 12, 12)
for post in posts.find({"date": {"$lt": d}}).sort("author"):
    pprint.pprint(post)

# index
result = db.profiles.create_index([('user_id', pymongo.ASCENDING)], unique=True)
sorted(list(db.profiles.index_information()))

user_profiles = [
    {'user_id': 211, 'name': 'Luke'},
    {'user_id': 212, 'name': 'Ziltoid'}]
result = db.profiles.insert_many(user_profiles)

new_profile = {'user_id': 213, 'name': 'Drew'}
duplicate_profile = {'user_id': 212, 'name': 'Tommy'}
result = db.profiles.insert_one(new_profile)  # This is fine.
try: 
    result = db.profiles.insert_one(duplicate_profile) # duplicate
except pymongo.errors.DuplicateKeyError:
    print ('> duplciated item inserted')

# remove match
print (posts.count_documents({}))
db.posts.remove ({"author": "Mike"})
print (posts.count_documents({}))

# remove all
db.posts.delete_many ({})
print (posts.count_documents({}))
db.profiles.remove ({})