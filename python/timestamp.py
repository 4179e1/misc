import time
import datetime

# return the seconds elapsed since 1970, the value overflow in 2038, well we still have 22 years
t = time.time()
print (t)

d = datetime.datetime.fromtimestamp (t)
print (d.strftime("%Y %B %d %H:%M.%f"))

