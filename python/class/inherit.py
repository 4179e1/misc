class Filter:
    def init(self):
        self.blocked=[]
    def filter(self,sequence):
        return [x for x in sequence if x not in self.blocked]

class SPAMFilter(Filter):
    def init (self):
        self.blocked=['SPAM']

s = [1,2,3,'SPAM', 'HAHA']
f = Filter()
f.init()
print (f.filter(s))

spam = SPAMFilter()
spam.init()
print (spam.filter(s))

print (issubclass(SPAMFilter, Filter))
print (issubclass(Filter, SPAMFilter))
print (SPAMFilter.__bases__)
print (Filter.__bases__)
print (isinstance(spam,SPAMFilter) )
print (isinstance(spam,Filter) )
print (spam.__class__)

