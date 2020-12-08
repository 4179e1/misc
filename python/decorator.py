#!/usr/bin/env python

import time
from datetime import datetime


def timeit(func):
    def _timeit (*args, **kwargs):
        t1 = datetime.now()
        r = func(*args, **kwargs)
        t2 = datetime.now()
        
        print("{} cost {}".format(func.__name__, t2 - t1))

    return _timeit

@timeit
def mysleep(i):
    time.sleep(i)

if __name__ == "__main__":
    mysleep(1)