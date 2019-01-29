# Makefile for MPI stubs library

# Syntax:
#   make                 # build lib as libmpi_stubs.a
#   make clean           # remove *.o and lib files

# edit System-specific settings as needed for your platform


# .DEFAULT:
# 	@if [ $@ = "serial" -a ! -f STUBS/libmpi_stubs.a ]; \
# 	  then $(MAKE) mpi-stubs; fi

# subsystem:
        # $(MAKE) -C subdir

EXE = ../../ljmd_serial.x
CC = gcc

CFLAGS = -I ../../include -I . -Wall -Wextra # -fPIC -O
LDFLAGS = -lm
OBJS = ../mdsys_force.o ../mdsys_input.o ../mdsys_output.o ../mdsys_util.o ../mdsys_velverlet.o ../mdsys_mpi.o mpi.o

# LIB_LDFLAGS = -shared -Wall -lm
# LIB_OBJS = ../mdsys_force.o ../mdsys_input.o ../mdsys_output.o ../mdsys_util.o ../mdsys_velverlet.o ../mdsys_mpi.o mpi.o


default: $(EXE)

# c serial compilation
$(EXE): ../ljmd.o
$(EXE): $(OBJS)
	$(CC) $^ -o $@  $(LDFLAGS)


# shared library compilation
libserialmd.so: CFLAGS += -fPIC -O
libserialmd.so: LDFLAGS += -shared
libserialmd.so: $(OBJS)
	$(CC) $^ -o $@  $(LDFLAGS)


%.o: %.c
	$(CC) -c $< -o $@  $(CFLAGS) 


../ljmd.o: ../../include/mdsys_struct.h ../../include/mdsys_input.h ../../include/mdsys_force.h
../mdsys_input.o: ../../include/mdsys_input.h  
../mdsys_force.o: ../../include/mdsys_force.h ../../include/mdsys_bc.h ../../include/mdsys_struct.h
../mdsys_output.o: ../../include/mdsys_output.h
../mdsys_util.o: ../../include/mdsys_util.h
../mdsys_velverlet.o: ../../include/mdsys_velverlet.h ../../include/mdsys_struct.h
../mdsys_mpi.o: ../../include/mdsys_mpi.h
./mpi.o: mpi.h


clean:
	rm -f *~ *.so *.o ../*.o *.x

# data.so: data.c
	# gcc -o $@ -shared -fPIC -Wal