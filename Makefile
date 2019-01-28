# -*- Makefile -*-
SHELL=/bin/sh

CC=mpicc
CFLAGS= -I./include -Wall -Wextra -O3
LDFLAGS= -lm
DEBUG= -g -ggdb
 
EXE=ljmd.x
OBJS=src/mdsys_force.o src/ljmd.o src/mdsys_input.o src/mdsys_output.o src/mdsys_bc.o src/mdsys_util.o \
src/mdsys_velverlet.o src/mdsys_mpi.o


default: $(EXE)

$(EXE): $(OBJS)
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@  $(CFLAGS) 

ljmd.o: include/mdsys_struct.h include/mdsys_input.h include/mdsys_bc.h  include/mdsys_force.h
mdsys_input.o: include/mdsys_input.h  
mdsys_bc.o: include/mdsys_bc.h	
mdsys_force.o: include/mdsys_force.h include/mdsys_bc.h include/mdsys_struct.h
mdsys_output.o: include/mdsys_output.h
mdsys_util.o: include/mdsys_util.h
mdsys_velverlet.o: include/mdsys_velverlet.h include/mdsys_struct.h
mdsys_mpi.o: include/mdsys_mpi.h mpi.h

clean:
	rm -rf $(OBJS) *~ $(EXE) *.png ./test/*.x


check: ./ljmd.x
	./ljmd.x < ./test/check/argon_108.inp
	head -10 ./test/check/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> ./test/check/a.dat
	head -10 ./test/reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> ./test/check/b.dat
	cmp ./test/check/a.dat ./test/check/b.dat || exit 1
	rm -f ./test/check/a.dat ./test/check/b.dat ./test/check/argon_108.dat ./test/check/argon_108.xyz


# Make test
test: test_force test_velverlet test_ekin test_input
	./test/test_force.x
	./test/test_velverlet.x
	./test/test_ekin.x
	./test/test_input.x < ./test/check/argon_108.inp

test_force: 
	$(CC) ./test/test_force.c ./src/mdsys_force.c ./src/mdsys_bc.c ./src/mdsys_util.c -o ./test/test_force.x -I ./include -lm

test_velverlet:
	$(CC) ./test/test_velverlet.c ./src/mdsys_velverlet.c -o ./test/test_velverlet.x -I ./include -lm
	
test_ekin:
	$(CC) ./test/test_ekin.c ./src/mdsys_force.c ./src/mdsys_util.c ./src/mdsys_bc.c -o ./test/test_ekin.x -I ./include -lm
	
test_input:
	$(CC) ./test/test_input.c ./src/mdsys_input.c ./src/mdsys_util.c -o ./test/test_input.x -I ./include -lm


.PHONY: default debug test benchmark clean

# default: serial

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

