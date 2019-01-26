#!/usr/bin/env python

from sqlalchemy import create_engine,Sequence
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String

engine = create_engine('sqlite:///:memory:', echo=True)
Base = declarative_base()

class User(Base):
    __tablename__ = 'users'
    id = Column(Integer, Sequence('user_id_seq'), primary_key=True)
    name = Column(String(50))
    fullname = Column(String(50))
    password = Column(String(12))

    def __repr__(self):
        return "<User(name='%s', fullname='%s', password='%s')>" % (
                                self.name, self.fullname, self.password)
    
'''
CREATE TABLE users (
        id INTEGER NOT NULL,
        name VARCHAR(50),
        fullname VARCHAR(50),
        password VARCHAR(12),
        PRIMARY KEY (id)
)
'''
Base.metadata.create_all(engine)