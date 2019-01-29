

## Best Practices in Scientific Computing

##### Ahmed Khalil (asaleh33), Federico Barone (Fede112) and Florentino Silva (fgoliveira87) 

We did an optimized version of the LJMD algorithm implemented serially and with MPI. We also implemented a python wrapper to run everything. Python handles all input and output.

To run the program follow these instructions:

* To build the serial version: `make serial`

  To run the serial version: `ljmd_serial.x ./test/check/argon_108.inp`

* To build the parallel version: `make parallel`

  To run the parallel version: ` mpirun -np # ./ljmd_parallel.x ./test/check/argon_108.inp` 

* To build the parallel library: `make parallel-lib`

* To build the serial library: `make serial-lib`

  The library is build at `src/serial/`

* The final python wrapper is inside `python-interface/`.

  To run it serially: ` python3 ljmd_wrapper.py -serial argon_108.inp `

  To run it in parallel: ` mpirun -np # python3 ljmd_wrapper.py -parallel argon_108.inp`

* To run the integration test: `make check`
* To run unittest for the c implementation of force, input, energy and velverlet: `make test`
* To run some time measurements in parallel: `make time108`or `make time2916`



**Important notice: run `make clean` between builds! (there are some dependencies because we didn't build everything with -fPIC) ** 