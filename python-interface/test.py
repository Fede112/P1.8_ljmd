#!/usr/bin/env python
from ctypes import *
import sys as sysf
def read_input(input_file): 
	# self._file = from_file_path
	input_param = []
	inout_files = []
	with open(input_file) as file: 
		for pc in file:
			try:              
				input_param.append(float(pc.split(' ')[0]))
			except:
				inout_files.append(pc.split(' ')[0])
	return input_param, inout_files
# take rest. file as an argument
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
	libC.azzero(mdsys.fx, mdsys.natoms)
	libC.azzero(mdsys.fy, mdsys.natoms)
	libC.azzero(mdsys.fz, mdsys.natoms)

	return


# output function
def set_output(file_traj, file_erg, mdsys):
	print mdsys.nfi, '\t', mdsys.temp,'\t', mdsys.ekin,'\t', mdsys.epot,'\t', mdsys.ekin + mdsys.epot
	file_erg.write('{} {} {} {} {} \n'.format(mdsys.nfi, mdsys.temp, mdsys.ekin, mdsys.epot, mdsys.ekin + mdsys.epot))        
	for i in range(sys.natoms):
		file_traj.write('Ar {} {} {} \n'.format(mdsys.rx[i], mdsys.ry[i], mdsys.rz[i] ))    
	return


# Loading dynamic link libraries
#libC = CDLL("./test.so")
libC = CDLL("./ljmd.so")
kboltz, mvsq2e = (c_double * 2)(*[0.0019872067, 2390.05736153349])
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



# .inp file read from input
input_file = sysf.argv[1]

# input_param: list of parameters to start md simulation
# inout_files: list of paths to the files for [restart (in), trajectory (out), energy(out)]
input_param, inout_files = read_input(input_file)

# print(input_param)
#print(inout_files) 

# populate sys with parameters
sys = mdsys_t(input_param)

# sys.nfi starts with the printing frequency, later we will overwrite it
nprint = sys.nfi


# initiate position and velocity
read_data(inout_files[0],sys)

#initialize forces and energies.
sys.nfi=0
libC.force(byref(sys))
libC.ekin(byref(sys))


print 'Starting simulation with', sys.natoms, 'atoms for', sys.nsteps,' steps.';
print "NFI \t TEMP \t EKIN \t EPOT \t ETOT";

with open(inout_files[1], 'w') as file_traj, open(inout_files[2], 'w') as file_erg: 
	# set trajectory and energies output files
	set_output(file_traj, file_erg, sys)

	for itr in xrange(1,sys.nsteps+1):
		sys.nfi=itr
		if (not (sys.nfi % nprint)):
			set_output(file_traj, file_erg, sys)
		libC.velverlet_1(byref(sys))
		libC.force(byref(sys))
		libC.velverlet_2(byref(sys))
		libC.ekin(byref(sys))

	file_traj.close()
	file_erg.close()


print "Simulation Done."





    
    #/* main MD loop */
    #for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

     #   /* write output, if requested */
     #   if ((sys.nfi % nprint) == 0)
     #       output(&sys, erg, traj);

     #   /* propagate system and recompute energies */
     #   velverlet_1(&sys);
     #   force(&sys);
     #   velverlet_2(&sys);
     #   ekin(&sys);





