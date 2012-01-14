k = "uid"
v = "sa"
print "%s=%s" % (k, v)

uid="sa"
pwd="secret"
print pwd + " is not a good password for " + uid
print "%s is not a good password for %s" % (pwd, uid)
userCount = 6
print "Users connected: %d " % (userCount, )
# error
# print "Users connected: " + userCount

print "Today's stock price: %f" % 50.4625
print "Today's stock price: %0.2f" % 50.4625
print "Change since yesterday: %+.2f" % 1.5
