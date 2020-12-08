import mongoengine as me

DATABASE = 'tumblelog'

db = me.connect(DATABASE)


class User(me.Document):
    email = me.StringField(required=True)
    first_name = me.StringField(max_length=50)
    last_name = me.StringField(max_length=50)

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        return "<User - id: `{}', first_name: `{}', last_name: `{}', email: `{}'>".format(self.id, self.first_name, self.last_name, self.email)


class Comment(me.EmbeddedDocument):
    content = me.StringField()
    name = me.StringField(max_length=120)


class Post(me.Document):
    title = me.StringField(max_length=120, required=True)
    author = me.ReferenceField(User, reverse_delete_rule=me.CASCADE)
    tags = me.ListField(me.StringField(max_length=30))
    comments = me.ListField(me.EmbeddedDocumentField(Comment))

    meta = {'allow_inheritance': True}

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        return "<Post - id: `{}', class: `{}', title: `{}', author: `{}', tags: `{}'>".format(self.id, self._cls, self.title, self.author, self.tags)


class TextPost(Post):
    content = me.StringField()


class ImagePost(Post):
    image_path = me.StringField()


class LinkPost(Post):
    link_url = me.StringField()


ross = User(email='ross@example.com', first_name='Ross',
            last_name='Lawley').save()


adam = User(email='adam@example.com', first_name='Adam',
            last_name='Smith').save()

john = User(email='john@example.com')
john.first_name = 'John'
john.last_name = 'Smith'
print("==> John before save: {}".format(john))
john.save()
print("==> John after save: {}".format(john))
print('==> ID type is {}'.format(type(john.id)))

print('==> find john by ObjectId')
u = User.objects.get(id=john.id)
print(u)
print('==> find john by string id')
u = User.objects.get(id=str(john.id))
print(u)

print('==> Who is the first one with Last Name Smith')
u = User.objects(last_name='Smith').first()
print(u)

print('==> Nobody with first name Alice')
u = User.objects(first_name='Alice').first()
print(u)


post1 = TextPost(title='Fun with MongoEngine', author=john)
post1.content = 'Took a look at MongoEngine today, looks pretty cool.'
post1.tags = ['mongodb', 'mongoengine']
post1.save()

post2 = LinkPost(title='MongoEngine Documentation', author=ross)
post2.link_url = 'http://docs.mongoengine.com/'
post2.tags = ['mongoengine']
post2.save()


print('==> ALL Posts')
for post in Post.objects:
    print(post.title)


print('==> ALL TextPosts')
for post in TextPost.objects:
    print(post.content)


print('==> Posts with tag mongodb')
for post in Post.objects(tags='mongodb'):
    print(post.title)

print('==> Post by John')

p = Post.objects(author=john).first()
print(p)

db.drop_database(DATABASE)
# User.drop_collection()
# Post.drop_collection()


# For find() you can do:
#   Cars.objects(model=2013)
#
# And for find_one() you can do:
#   Cars.objects.get(model=2013)
