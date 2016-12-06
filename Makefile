.PHONY: clean
CXX = g++
CXXFLAGS = -g -Wall -std=c++11

# compile with opencl
#INC = -I/sccs/nvd/OpenCL/include/ -I.
#LIB = -L/sccs/nvd/ocl-icd/2.2.9/lib/ -lOpenCL -lm

INC =-I.
LIB =

obj= Main.o flowField.o FlowField.o Stencil.o Simulation.o Run.o Etta.o m.o M.o Dz.o Parameters.o jacobiSolver.o helper.o simulation.o output.o

all: nhsw

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -c -o $@ $<

nhsw: $(obj)
	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -o $@ $+
	mkdir -p output

run:
	rm -f output/*
	./nhsw 10 10 12 3.5 0.1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 > output/log
struct:
	rm -f output/*
	./nhsw 2 2 2 3.5 0.1 0.5 2.0 2.0 2.0 2.0 9.81 0.000001787 0 0 0 0 > output/log
oscilation:
	rm -f output/*
	./nhsw 20 20 24 3.5 0.1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 > output/log
clean:
	rm -f *.o core.*
	rm -f nhsw
	rm -rf output
