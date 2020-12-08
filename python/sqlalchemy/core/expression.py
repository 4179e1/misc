#!/usr/bin/env python3

from sqlalchemy import create_engine, Sequence, and_, or_, text, func
from sqlalchemy import Column, Integer, String
from sqlalchemy.sql import exists
from sqlalchemy.orm import sessionmaker, aliased, selectinload, joinedload, contains_eager
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm.exc import MultipleResultsFound, NoResultFound

from schema import users, addresses, engine
conn = engine.connect()

#ins = users.insert()
ins = users.insert().values(name='jack', fullname='Jack Jones')
print(str(ins))
print(ins.compile().params)

result = conn.execute(ins)
print(result.inserted_primary_key)

# multiple insert
ins = users.insert()
conn.execute(ins, id=2, name='wendy', fullname='Wendy Williams')

conn.execute(addresses.insert(), [
    {'user_id': 1, 'email_address': 'jack@yahoo.com'},
    {'user_id': 1, 'email_address': 'jack@msn.com'},
    {'user_id': 2, 'email_address': 'www@www.org'},
    {'user_id': 2, 'email_address': 'wendy@aol.com'},
])
