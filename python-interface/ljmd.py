#!/usr/bin/env python

from ctypes import *

# Loading dynamic link libraries
libC = CDLL("./ljmd.so")


kboltz, mvsq2e = (c_double * 2)(*[0.0019872067, 2390.05736153349])

# to check: do print out variables, and then sum 

print kboltz, mvsq2e
result = kboltz + mvsq2e
print result


