.PHONY: clean
CXX = g++
CXXFLAGS = -g -Wall -std=c++11

# compile with opencl
#INC = -I/sccs/nvd/OpenCL/include/ -I.
#LIB = -L/sccs/nvd/ocl-icd/2.2.9/lib/ -lOpenCL -lm

INC =-I.
LIB =

obj= Main.o flowField.o FlowField.o Stencil.o StencilInvA.o Iterator.o Simulation.o zAz.o zAG.o Run.o Etta.o m.o M.o Dz.o Parameters.o AI_Inv.o AJ_Inv.o AK_Inv.o Solver.o JacobiSolverEtta.o jacobiSolver.o helper.o GI.o GJ.o GK.o U.o V.o W.o Q.o JacobiSolverQ.o Delta.o output.o

obj_test=Main.o flowField.o FlowField.o Stencil.o StencilInvA.o Iterator.o Simulation.o zAz.o zAG.o TestRun.o Etta.o m.o M.o Dz.o Parameters.o AI_Inv.o AJ_Inv.o AK_Inv.o Solver.o JacobiSolverEtta.o jacobiSolver.o helper.o GI.o GJ.o GK.o U.o V.o W.o Q.o JacobiSolverQ.o Delta.o output.o

all: nhsw test

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -c -o $@ $<

nhsw: $(obj)
	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -o $@ $+
	mkdir -p output

test: $(obj_test)
	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -o $@ $+
	mkdir -p output

testrun:
	rm -f output/*
	./test 4 4 6 3.5 0.01 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 > output/log

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
	rm -f nhsw test
	rm -rf output
clear:
	rm -f output/*
