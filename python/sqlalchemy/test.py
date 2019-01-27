#!/usr/bin/env python3

from sqlalchemy import create_engine,Sequence,and_,or_,text,func
from sqlalchemy import Column, Integer, String
from sqlalchemy.sql import exists
from sqlalchemy.orm import sessionmaker, aliased, selectinload, joinedload, contains_eager
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm.exc import MultipleResultsFound, NoResultFound

from schema import engine, Session, User, Address, BlogPost, Keyword


def create (session):
    ed_user = User (name='ed', fullname='Ed Jones', password='edspassword')
    print (ed_user, ed_user.id)
    session.add (ed_user)
    session.add_all([
        User(name='wendy', fullname='Wendy Williams', password='foobar'),
        User(name='mary', fullname='Mary Contrary', password='xxg527'),
        User(name='fred', fullname='Frd Flinstone', password='blah')])
    print (session.new)
    session.commit() # commit !!!!
    print (ed_user, ed_user.id)

    # update
    ed_user.password = 'f8s7ccs'
    print (session.dirty)
    session.commit() # commit !!!!

    # address
    jack = User (name="jack", fullname="Jack Bean", password='gjffdd')
    jack.addresses = [
        Address (email_address='jack@google.com'),
        Address (email_address='j25@yahoo.com'),
    ]
    session.add (jack)
    session.commit()

    print (jack.addresses)
    print ("==========================================")



def query (session):
    # query full
    for instance in session.query(User).order_by(User.id):
        print(instance.name, '-', instance.fullname)

    # query part
    for name, fullname in session.query(User.name, User.fullname):
        print(name, fullname)

    # query named tuple
    for row in session.query(User, User.name).all():
        #print(row)
        print(row.User, row.name)

    for row in session.query(User.name).all():
        #print(row)
        print(row.name)

    # label
    for row in session.query(User.name.label('name_label')).all():
       print(row.name_label)

    # alias
    user_alias = aliased(User, name='user_alias')
    for row in session.query(user_alias, user_alias.name).all():
       print(row.user_alias)

    # limit/offset
    for u in session.query(User).order_by(User.id)[1:3]:
       print(u)

    # filter_by
    for name, in session.query(User.name).filter_by(fullname='Ed Jones'):
       print(name)

    # filter
    for name, in session.query(User.name). filter(User.fullname=='Ed Jones'):
       print(name)

def filter_ (session):
    # equal
    for item in session.query(User).filter (User.name == 'ed'):
        print (item)

    # not equal
    for item in session.query(User).filter (User.name != 'ed'):
        print (item)

    # like
    for item in session.query(User).filter (User.name.like ('%ed%')):
        print (item)

    # in
    for item in session.query(User).filter(User.name.in_(['ed', 'wendy', 'jack'])):
        print (item)
    
    for item in session.query(User).filter(User.name.in_(
        session.query(User.name).filter(User.name.like('%ed%'))
    )):
        print (item)

    # not in, the ~
    for item in session.query(User).filter(~User.name.in_(['ed', 'wendy', 'jack'])):
        print (item)

    # is null
    for item in session.query(User).filter(User.name == None):
        print (item)

    # is not null
    for item in session.query(User).filter(User.name != None):
        print (item)

    ## AND
    for item in session.query(User).filter(and_(User.name == 'ed', User.fullname == 'Ed Jones')):
        print (item)

    # or send multiple expressions to .filter()
    for item in session.query(User).filter(User.name == 'ed', User.fullname == 'Ed Jones'):
        print (item)

    # or chain multiple filter()/filter_by() calls
    for item in session.query(User).filter(User.name == 'ed').filter(User.fullname == 'Ed Jones'):
        print (item)

    # OR
    for item in session.query(User).filter(or_(User.name == 'ed', User.name == 'wendy')):
        print (item)

    # Match: donno, it doesn't work on MySQL
    #for item in session.query(User).filter(User.name.match('wendy')):
    #    print (item)


def lists (session):
    query = session.query(User).filter(User.name.like('%ed')).order_by(User.id)
    print (query.all())

    print (query.first())

    try:
        print (query.one())
    except MultipleResultsFound as e:
        print ("Multiple record found")
    except NoResultFound:
        print ("No record found")

    try:
        print (query.one_or_none())
    except MultipleResultsFound as e:
        print ("Multiple record found")

    # similar to one()... but what's the difference?
    #print (query.scalar())
    
def textual (session: Session): 
    for user in session.query(User).filter (text("id<99999")).order_by(text("id")).all():
        print (user.name)

    #params
    user = session.query(User).filter (text("id<:value and name=:name")).\
        params(value=99999, name='fred').order_by(User.id).scalar()
    print (user)

    # pure text
    for user in session.query(User).from_statement(
                    text("SELECT * FROM users where name=:name")).\
                    params(name='ed').all():
        print (user)

    # matching statement
    stmt = text("SELECT name, id, fullname, password "
            "FROM users where name=:name")
    stmt = stmt.columns(User.name, User.id, User.fullname, User.password)

    for user in session.query(User).from_statement(stmt).params(name='ed').all():
        print (user)

    stmt = text("SELECT name, id FROM users where name=:name")
    stmt = stmt.columns(User.name, User.id)
    
    for user in session.query(User.id, User.name).\
             from_statement(stmt).params(name='ed').all():
        print (user)

def count (session):
    print (session.query(User).filter(User.name.like('%ed')).count())

    for item in session.query(func.count(User.name), User.name).group_by(User.name).all():
        print (item)

    # what is select_from?
    print (session.query(func.count('*')).select_from(User).scalar())

    # user primary key
    print (session.query(func.count(User.id)).scalar())

def join (session: Session) -> None:
    for u, a in session.query (User, Address).\
            filter (User.id==Address.user_id).\
            filter (Address.email_address=='jack@google.com').all():
        print (u)
        print (a)

    for item in session.query(User.name, Address.email_address).join(Address).\
            filter(Address.email_address=='jack@google.com').\
            all():
        print (item)

    # candidates
    # query.join(Address, User.id==Address.user_id)    # explicit condition
    # query.join(User.addresses)                       # specify relationship from left to right
    # query.join(Address, User.addresses)              # same, with explicit target
    # query.join('addresses')                          # same, using a string
    
    #outer join
    for item in session.query(User.name, Address.email_address).outerjoin(Address).all():
        print (item)

    # alias
    adalias1 = aliased (Address)
    adalias2 = aliased (Address)
    for username, email1, email2 in \
            session.query(User.name, adalias1.email_address, adalias2.email_address).\
            join(adalias1, User.addresses).\
            join(adalias2, User.addresses).\
            filter(adalias1.email_address=='jack@google.com').\
            filter(adalias2.email_address=='j25@yahoo.com'):
        print(username, email1, email2)

def subquery (session):
    '''
    SELECT users.*, adr_count.address_count FROM users LEFT OUTER JOIN
    (SELECT user_id, count(*) AS address_count
        FROM addresses GROUP BY user_id) AS adr_count
    ON users.id=adr_count.user_id
    '''

    stmt = session.query (Address.user_id, func.count('*').label('address_count')).\
            group_by (Address.user_id).subquery()

    for u, count in session.query (User, stmt.c.address_count).\
            outerjoin (stmt, User.id==stmt.c.user_id).order_by (User.id):
        print (u,count)

    # select entities from subqueries
    stmt = session.query (Address).filter (Address.email_address != 'j25@yahoo.com').subquery()
    adalias = aliased (Address, stmt) # what did you do ?
    for user, address in session.query (User, adalias).join (adalias, User.addresses):
        print (user)
        print (address)

    #exists
    stmt = exists().where(Address.user_id == User.id)
    for name, in session.query (User.name).filter (stmt):
        print (name)

    #exists alternative
    for name, in session.query (User.name).filter (User.addresses.any()):
        print (name)

    for name, in session.query(User.name).\
        filter(User.addresses.any(Address.email_address.like('%google%'))):
        print(name)

    # has
    for name, in session.query(User.name).\
        filter(~Address.user.has(User.name=='jack')):
        print(name)

def eager_selectinload (session):
    alex = User (name="alex", fullname="Alex pooh", password='gjffdd')
    alex.addresses = [
        Address (email_address='alex@google.com'),
        Address (email_address='alex@yahoo.com'),
    ]
    session.add (alex)
    session.commit()

    # selectinload, what does it do?
    alex = session.query (User).options (selectinload(User.addresses)).filter_by (name='alex').one()
    print (alex)
    print (alex.addresses)

    # joined load
def eager_joinedload (session):
    alex = User (name="alex", fullname="Alex pooh", password='gjffdd')
    alex.addresses = [
        Address (email_address='alex@google.com'),
        Address (email_address='alex@yahoo.com'),
    ]
    session.add (alex)
    session.commit()

    # selectinload, what does it do?
    alex = session.query (User).options (joinedload(User.addresses)).filter_by (name='alex').one()
    print (alex)
    print (alex.addresses)

        
def eager_explicit (session):
    alex = User (name="alex", fullname="Alex pooh", password='gjffdd')
    alex.addresses = [
        Address (email_address='alex@google.com'),
        Address (email_address='alex@yahoo.com'),
    ]
    session.add (alex)
    session.commit()

    # selectinload, what does it do?
    alex_address = session.query(Address).\
                            join(Address.user).\
                            filter(User.name=='alex').\
                            options(contains_eager(Address.user)).\
                            all()
    print (alex_address)


def delete_ (session: Session) -> None:
    jack = session.query(User).filter (User.name=='jack').scalar()
    session.delete(jack)
    print (session.query(User).filter_by(name='jack').count())

def many (session):
    wendy = session.query(User).\
                    filter_by(name='wendy').\
                    one()
    post = BlogPost("Wendy's Blog Post", "This is a test", wendy)
    session.add(post)

    post.keywords.append(Keyword('wendy'))
    post.keywords.append(Keyword('firstpost'))

    session.commit()

    for item in session.query(BlogPost).\
             filter(BlogPost.keywords.any(keyword='firstpost')).\
             all():
        print (item)

    # alt
    for item in session.query(BlogPost).\
            filter(BlogPost.author==wendy).\
            filter(BlogPost.keywords.any(keyword='firstpost')).\
            all():
        print (item)

    print ('---')
    for item in wendy.posts.filter(BlogPost.keywords.any(keyword='firstpost')).all():
        print (item)
    print ('---')


if __name__ == "__main__":
    # create one for database transaction
    session = Session()

    create (session)
    #query (session)
    #filter_ (session)
    #lists (session)
    #textual (session)
    #count (session)
    #join (session)
    #subquery (session)
    #eager_selectinload (session)
    #eager_joinedload (session)
    #eager_explicit (session)

    #delete_ (session)

    many(session)

    session.close()