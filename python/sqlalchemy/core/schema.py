#!/usr/bin/env python3

import sys
import os
from sqlalchemy import create_engine, Table, Column, Integer, String, MetaData, ForeignKey

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
engine = create_engine(
    'mysql+pymysql://sqlalchemy:sqlalchemy@localhost/sqlalchemy', echo=True)

'''
CREATE TABLE users (
        id INTEGER NOT NULL,
        name VARCHAR(50),
        fullname VARCHAR(50),
        password VARCHAR(12),
        PRIMARY KEY (id)
)
'''
metadata = MetaData()
users = Table('users', metadata,
              Column('id', Integer, primary_key=True),
              Column('name', String(64)),
              Column('fullname', String(64)),
              )

addresses = Table('addresses', metadata,
                  Column('id', Integer, primary_key=True),
                  Column('user_id', None, ForeignKey('users.id')),
                  Column('email_address', String(64), nullable=False)
                  )


def usage() -> None:
    sys.stderr.write("""
 {0} <create|drop|delete>    

 """.format(sys.argv[0].split('/')[-1]))


TABLES = [addresses, users]

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()
        sys.exit(1)
    action = sys.argv[1]

    if action.lower() == "create":
        metadata.create_all(engine)
    elif action.lower() == "drop":
        metadata.drop_all(bind=engine, tables=TABLES)
    elif action.lower() == "delete":
        conn = engine.connect()
        for table in TABLES:
            d = table.delete()
            conn.execute(d)
    else:
        usage()
        sys.exit(1)
