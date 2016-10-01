.PHONY: clean
CXX = g++
CXXFLAGS = -g Wall -std=c++11

# compile with opencl
#INC = -I/sccs/nvd/OpenCL/include/ -I.
#LIB = -L/sccs/nvd/ocl-icd/2.2.9/lib/ -lOpenCL -lm

INC =-I.
LIB =

obj= main.o flowField.o Parameters.o jacobiSolver.o


all: nhsw

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

nhsw: $(obj)
	$(CXX) $(CFLAGS) $(INC) $(LIB) -o $@ $+

run:
	./nhsw 10 10 10 3.5 0.1 10.0 10.0 10.0

clean:
	rm -f *.o core.*
	rm -f nhsw
