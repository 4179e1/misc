#!/usr/bin/env python3
from pymongo import MongoClient

cli = MongoClient()
db = cli['test_database']

for col in db.collection_names():
    db[col].drop()
