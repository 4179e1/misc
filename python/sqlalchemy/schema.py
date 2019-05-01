#!/usr/bin/env python3

import sys,os
from sqlalchemy import create_engine,Sequence,ForeignKey, Table, Text
from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import sessionmaker,relationship
from sqlalchemy.ext.declarative import declarative_base

'''
mysql init:

# mysql_install_db --user=mysql
# systemctl start mysql
# /usr/bin/mysql_secure_installation

> create database sqlalchemy
> GRANT ALL PRIVILEGES ON `sqlalchemy`.* TO 'sqlalchemy'@'%' IDENTIFIED BY 'sqlalchemy';
> CREATE USER 'sqlalchemy'@'%' IDENTIFIED BY 'sqlalchemy';
> GRANT ALL ON `sqlalchemy`.* TO 'sqlalchemy'@'%';

'''

#engine = create_engine('sqlite:///:memory:', echo=True)
engine = create_engine('mysql+pymysql://sqlalchemy:sqlalchemy@localhost/sqlalchemy', echo=True)
# Create it only once
Session = sessionmaker (bind=engine)

Base = declarative_base()

'''
CREATE TABLE users (
        id INTEGER NOT NULL,
        name VARCHAR(50),
        fullname VARCHAR(50),
        password VARCHAR(12),
        PRIMARY KEY (id)
)
'''
class User(Base):
    __tablename__ = 'users'
    id = Column(Integer, Sequence('user_id_seq'), primary_key=True)
    name = Column(String(50), nullable=False)
    fullname = Column(String(50))
    password = Column(String(12))

    def __repr__(self):
        return "<User(name='%s', fullname='%s', password='%s')>" % (
                                self.name, self.fullname, self.password)
    

class Tb1 (Base):
    __tablename__ = 'tb1'
    id = Column(Integer, Sequence('entity_seq'), primary_key=True)
    entity = Column(String(32), index=True)
    attribute = Column(String(32), index=True)
    value = Column(String(32), index=True)

class Address(Base):
    __tablename__ = 'addresses'
    id = Column(Integer, primary_key=True)
    email_address = Column (String(50), nullable=False)
    user_id = Column (Integer, ForeignKey ('users.id'))

    # many to one
    user = relationship ('User', back_populates="addresses")

    def __repr__ (self):
        return "<Address(email_address='%s'>" % self.email_address

"""
Two end binding

by doing so, each relationship() can make intelligent decision about the same relationship as expressed in reverse; 
on one side, Address.user refers to a User instance, and on the other side, 
User.addresses refers to a list of Address instances.
"""    
User.addresses = relationship ('Address', order_by=Address.id, back_populates="user")


# Many to Many
# association table
post_keywords = Table('post_keywords', Base.metadata,
    Column('post_id', ForeignKey('posts.id'), primary_key=True),
    Column('keyword_id', ForeignKey('keywords.id'), primary_key=True)
)

class BlogPost(Base):
    __tablename__ = 'posts'

    id = Column(Integer, primary_key=True)
    user_id = Column(Integer, ForeignKey('users.id'))
    headline = Column(String(255), nullable=False)
    body = Column(Text)

    # many to many BlogPost<->Keyword
    keywords = relationship('Keyword',
                            secondary=post_keywords,
                            back_populates='posts')

    def __init__(self, headline, body, author):
        self.author = author
        self.headline = headline
        self.body = body

    def __repr__(self):
        return "BlogPost(%r, %r, %r)" % (self.headline, self.body, self.author)


class Keyword(Base):
    __tablename__ = 'keywords'

    id = Column(Integer, primary_key=True)
    keyword = Column(String(50), nullable=False, unique=True)
    posts = relationship('BlogPost',
                         secondary=post_keywords,
                         back_populates='keywords')

    def __init__(self, keyword):
        self.keyword = keyword

BlogPost.author = relationship(User, back_populates="posts")
User.posts = relationship(BlogPost, back_populates="author", lazy="dynamic")


def usage () -> None:
    sys.stderr.write ("""
 {0} <create|drop|delete>    

 """.format (sys.argv[0].split('/')[-1]))


if __name__ == "__main__":
    if len (sys.argv) < 2:
        usage()
        sys.exit (1)
    action = sys.argv[1]

    if action.lower() == "create":
        Base.metadata.create_all(engine)
    elif action.lower() == "drop":
        #User.__table__.drop(engine)
        Base.metadata.drop_all(bind=engine, tables=[post_keywords, BlogPost.__table__, Keyword.__table__, Address.__table__, User.__table__])
        pass
    elif action.lower() == "delete":
        session = Session()

        conn = engine.connect()
        conn.execute (post_keywords.delete())

        session.query(BlogPost).delete()
        session.query(Keyword).delete()
        session.query(Address).delete()
        session.query(User).delete()
        session.commit()
        session.close()
    else:
        usage()
        sys.exit(1)
