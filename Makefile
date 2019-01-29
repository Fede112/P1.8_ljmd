# -*- Makefile -*-
SHELL=/bin/sh

CC=mpicc
CFLAGS= -I./include -Wall -Wextra -O3 -ffast-math -fexpensive-optimizations -msse3

LDFLAGS= -lm
DEBUG= -g -ggdb

SO = ./python-interface/libparallelmd.so
EXE = ljmd_parallel.x
OBJS = src/mdsys_force.o src/mdsys_input.o src/mdsys_output.o src/mdsys_util.o src/mdsys_velverlet.o src/mdsys_mpi.o


default: parallel

$(EXE): src/ljmd.o 
$(EXE): $(OBJS)
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@  $(CFLAGS) 

parallel:$(EXE) 


parallel-lib: CFLAGS += -fPIC
parallel-lib: LDFLAGS += -shared -Wl,-rpath,/usr/lib/x86_64-linux-gnu/openmpi/lib -rdynamic
parallel-lib: $(OBJS)
	$(CC) $^ -o $(SO)  $(LDFLAGS)

serial:
	$(MAKE) -C ./src/serial

serial-lib:
	$(MAKE) libserialmd.so -C ./src/serial


src/ljmd.o: include/mdsys_struct.h include/mdsys_input.h include/mdsys_force.h
src/mdsys_input.o: include/mdsys_input.h  
src/mdsys_force.o: include/mdsys_force.h include/mdsys_bc.h include/mdsys_struct.h
src/mdsys_output.o: include/mdsys_output.h
src/mdsys_util.o: include/mdsys_util.h
src/mdsys_velverlet.o: include/mdsys_velverlet.h include/mdsys_struct.h
src/mdsys_mpi.o: include/mdsys_mpi.h

#serial
src/test/mpi.o: include/mpi.h

clean:
	rm -rf $(OBJS) *~ $(EXE) ./test/*.x *.x *.so ./python-interface/*.so
	$(MAKE) clean -C ./src/serial




# ALL PURPOSE TESTS

check: ./ljmd.x
	./ljmd.x < ./test/check/argon_108.inp
	head -10 ./test/check/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> ./test/check/a.dat
	head -10 ./test/reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> ./test/check/b.dat
	cmp ./test/check/a.dat ./test/check/b.dat || exit 1
	rm -f ./test/check/a.dat ./test/check/b.dat ./test/check/argon_108.dat ./test/check/argon_108.xyz


# Make test
test: test_force test_velverlet test_ekin test_input
	#./test/test_force.x 
	./test/test_velverlet.x
	./test/test_ekin.x
	./test/test_input.x ./test/check/argon_108.inp

test_force: 
#	$(CC) ./test/test_force.c ./src/mdsys_force.c ./src/mdsys_util.c -o ./test/test_force.x -I ./include -lm

test_velverlet:
	$(CC) ./test/test_velverlet.c ./src/mdsys_velverlet.c -o ./test/test_velverlet.x -I ./include -lm
	
test_ekin:
	$(CC) ./test/test_ekin.c ./src/mdsys_force.c ./src/mdsys_util.c -o ./test/test_ekin.x -I ./include -lm
	
test_input:
	$(CC) ./test/test_input.c ./src/mdsys_input.c ./src/mdsys_util.c -o ./test/test_input.x -I ./include -lm

time108: ljmd_parallel.x
	/usr/bin/time -p mpirun ./ljmd_parallel.x ./test/check/argon_108.inp #-o profiling/time_record_mpi.dat -a

time2916: ljmd_parallel.x
	/usr/bin/time -p mpirun ./ljmd_parallel.x ./examples/argon_2916.inp #-o profiling/time_record_mpi2916.dat -a

.PHONY: default debug test benchmark clean

# serial: CFLAGS += -I ./src/serial/ 
# serial: $(EXE)
# serial:
# 	$(MAKE) -C ./src/serial





# serial:
# 	$(MAKE) $(MFLAGS) -C Obj-$@

# clean:
# 	$(MAKE) $(MFLAGS) -C Obj-serial clean
# 	$(MAKE) $(MFLAGS) -C examples clean

# check: serial
# 	$(MAKE) $(MFLAGS) -C examples check


# src/binarytree.o: include/binarytree.h include/iterator.h

# debug: CFLAGS += $(DEBUG) -DTEST
# debug: default
# debug: 
# 	valgrind ./${EXE} 


# test: CXXFLAGS += -DTEST
# test: default

