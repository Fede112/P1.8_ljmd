#!/usr/bin/env python

from ctypes import *
import sys as sysf


# usage message
if len(sysf.argv) != 2:
    print "Usage:", sysf.argv[0], "argon_108.inp" 
    sysf.exit(1)


# read .inp file, take parameters, and name output files

def read_input(input_file): 
    input_param, inout_files = [], []
    with open(input_file) as file: 
        for pc in file:
            try:              
                input_param.append(float(pc.split(' ')[0]))
            except:
                inout_files.append(pc.split(' ')[0])
    return input_param, inout_files


# Loading dynamic link libraries
libC = CDLL("./ljmd.so")


kboltz, mvsq2e = (c_double * 2)(*[0.0019872067, 2390.05736153349])

# to check: do print out variables, and then sum 
print kboltz, mvsq2e
result = kboltz + mvsq2e
print result

# ctypes structures:

class mdsys_t(Structure):
  _fields_ = [
    ('natoms', c_int),
    ('nfi', c_int), 
    ('nsteps', c_int),
    ('dt', c_double),
    ('mass', c_double),
    ('epsilon', c_double),
    ('sigma', c_double),
    ('box', c_double),
    ('rcut', c_double),
    ('ekin', c_double),
    ('epot', c_double),
    ('temp', c_double),
    ('rx', POINTER(c_double)), 
    ('ry', POINTER(c_double)), 
    ('rz', POINTER(c_double)), 
    ('vx', POINTER(c_double)), 
    ('vy', POINTER(c_double)),  
    ('vz', POINTER(c_double)), 
    ('fx', POINTER(c_double)), 
    ('fy', POINTER(c_double)), 
    ('fz', POINTER(c_double)),      
  ]  


input_file = sysf.argv[1]
input_param, inout_files = read_input(input_file)

'''
# to check the structure
sys = mdsys_t()
sys.natoms=100

sys.ekin=5.0

print("sys natoms:{}, fy:{}, ekin:{}".format(sys.natoms, sys.fy, sys.ekin))


# testing structure using a dummy function from the source code

sys.natoms=20 
ilist = (c_int * sys.natoms)()

test = libC.print_test(ilist, sys.natoms)
print "print from python: ", sys.natoms
'''

