# -*- Makefile -*-
SHELL=/bin/sh

CC=gcc
CFLAGS= -I./include -Wall -Wextra -O3
LDFLAGS= -lm
DEBUG= -g -ggdb
 
EXE=ljmd.x
OBJS=src/mdsys_force.o src/ljmd.o src/mdsys_input.o src/mdsys_output.o src/mdsys_bc.o src/mdsys_util.o src/mdsys_velverlet.o


default: $(EXE)

$(EXE): $(OBJS)
	$(CC) $^ -o $@  $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@  $(CFLAGS) 

ljmd.o: include/mdsys_struct.h include/mdsys_input.h include/mdsys_bc.h  include/mdsys_force.h
mdsys_input.o: include/mdsys_input.h  
mdsys_pbc.o: include/mdsys_pbc.h	
mdsys_force.o: include/mdsys_force.h include/mdsys_pbc.h include/mdsys_struct.h
mdsys_output.o: include/mdsys_output.h
mdsys_util.o: include/mdsys_util.h
mdsys_velverlet.o: include/mdsys_velverlet.h include/mdsys_struct.h

clean:
	rm -rf $(OBJS) *~ $(EXE) *.png 


check: ./ljmd.x
	./ljmd.x < ./check/argon_108.inp
	head -10 ./check/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> ./check/a.dat
	head -10 ./reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$$1,$$2,$$3,$$4);}'> ./check/b.dat
	cmp ./check/a.dat ./check/b.dat || exit 1
	rm -f ./check/a.dat ./check/b.dat ./check/argon_108.dat ./check/argon_108.xyz


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

