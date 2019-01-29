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



# read .rest file 
def read_data(inputfile, mdsys):
    file = open(inputfile, "r")
    for i, line in enumerate(file):
        sep = line.strip().split()
        if 0 <= i < mdsys.natoms:
            mdsys.rx[i] = float(sep[0])
            mdsys.ry[i] = float(sep[1])
            mdsys.rz[i] = float(sep[2])
        else:
            mdsys.vx[i-mdsys.natoms] = float(sep[0]) 
            mdsys.vy[i-mdsys.natoms] = float(sep[1])  
            mdsys.vz[i-mdsys.natoms] = float(sep[2]) 
    return



# output function
def get_output(outputfile_traj, outputfile_erg, mdsys):
    print(mdsys.nfi, mdsys.temp, mdsys.ekin, mdsys.epot, mdsys.ekin + mdsys.epot)
    with open(outputfile_traj, 'w') as traj, open(outputfile_erg, 'w') as erg: 
	erg.write('{} {} {} {} {} \n'.format(mdsys.nfi, mdsys.temp, mdsys.ekin, mdsys.epot, mdsys.ekin + mdsys.epot))        
	for i in range(sys.natoms):
            traj.write('Ar {} {} {} \n'.format(mdsys.rx[i], mdsys.ry[i], mdsys.rz[i] ))    
        traj.close()
        erg.close()
    return

# Loading dynamic link libraries
libC = CDLL("./ljmd.so")


kboltz, mvsq2e = (c_double * 2)(*[0.0019872067, 2390.05736153349])

# to check: do print out variables, and then sum 
print kboltz, mvsq2e
result = kboltz + mvsq2e
print result

# ctypes structures and setting constructor:

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

    def __init__(self, input_param):
        # for field_name, field_type in sys._fields_:
        # print setattr(sys, field_name, input_list[0])
        self.natoms = int(input_param[0])
        self.nfi = int(input_param[8])
        self.nsteps = int(input_param[6])
        self.dt = input_param[7]
        self.mass = input_param[1]
        self.epsilon = input_param[2]
        self.sigma = input_param[3]
        self.box = input_param[5]
        self.rcut = input_param[4]
        self.rx = (c_double * self.natoms)()
        self.ry = (c_double * self.natoms)()
        self.rz = (c_double * self.natoms)()
        self.vx = (c_double * self.natoms)()
        self.vy = (c_double * self.natoms)()
        self.vz = (c_double * self.natoms)()
        self.fx = (c_double * self.natoms)()
        self.fy = (c_double * self.natoms)()
        self.fz = (c_double * self.natoms)()
		


input_file = sysf.argv[1]
input_param, inout_files = read_input(input_file)
print(input_param, inout_files)
# populate sys with parameters
sys = mdsys_t(input_param)

# initiate position and velocity
read_data(inout_files[0],sys)

# get trajectory and energies output files
get_output(inout_files[1], inout_files[2], sys)


#calling forces and energies, as a test. It works!
#sys.nfi=0
#libC.force(byref(sys))
#libC.ekin(byref(sys))

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

