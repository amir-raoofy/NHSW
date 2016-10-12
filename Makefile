.PHONY: clean
CXX = g++
CXXFLAGS = -g Wall -std=c++11

# compile with opencl
#INC = -I/sccs/nvd/OpenCL/include/ -I.
#LIB = -L/sccs/nvd/ocl-icd/2.2.9/lib/ -lOpenCL -lm

INC =-I.
LIB =

obj= main.o flowField.o Parameters.o jacobiSolver.o helper.o simulation.o


all: nhsw

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

nhsw: $(obj)
	$(CXX) $(CFLAGS) $(INC) $(LIB) -o $@ $+

run:
	./nhsw 3 3 5 3.5 0.1 0.5 3.0 3.0 5.0 9.81 0.000001787 0 0 0 0
clean:
	rm -f *.o core.*
	rm -f nhsw
