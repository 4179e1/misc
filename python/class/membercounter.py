class MemberCounter:
    members = 0
    another = 0
    def init(self):
        # global
        MemberCounter.members += 1
        # instance
        self.another = MemberCounter.members

m = MemberCounter()
m.init()
print (MemberCounter.members)
print (MemberCounter.another)
print (m.members)
print (m.another)
