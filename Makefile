.PHONY: clean
#CXX = g++
CXX = mpicxx
#CXX = mpiCC
CXXFLAGS = -Wall -std=c++11
#CXXFLAGS = -g -O2 -qopt-report -Wall -std=c++11

#INC =-I.
#LIB =

# compile with opencl
#INC = -I/sccs/nvd/OpenCL/include/ -I.
#LIB = -L/sccs/nvd/ocl-icd/2.2.9/lib/ -lOpenCL -lm

#compile with petsc
INC = -I. $(PETSC_INC) ${PETSC_CC_INCLUDES}
LIB = $(PETSC_LIB)

obj= Main.o FlowField.o Simulation.o zAz.o zAG.o Run.o Etta.o m.o M.o Dz.o Parameters.o AI_Inv.o AJ_Inv.o AK_Inv.o Solver.o JacobiSolverEtta.o ParallelJacobiSolverEtta.o  ParallelSolverEtta.o GI.o GJ.o GK.o U.o V.o W.o Q.o JacobiSolverQ.o Delta.o output.o Topology.o CommunicationManager.o

obj_test= Main.o FlowField.o Simulation.o zAz.o zAG.o TestRun.o Etta.o m.o M.o Dz.o Parameters.o AI_Inv.o AJ_Inv.o AK_Inv.o Solver.o JacobiSolverEtta.o ParallelJacobiSolverEtta.o ParallelSolverEtta.o GI.o GJ.o GK.o U.o V.o W.o Q.o JacobiSolverQ.o Delta.o output.o Topology.o CommunicationManager.o

obj_petsc= Main.o FlowField.o Simulation.o PetscZAZ.o PetscZAG.o Run.o Etta.o m.o M.o Dz.o Parameters.o AI_Inv.o AJ_Inv.o AK_Inv.o Solver.o JacobiSolverEtta.o ParallelJacobiSolverEtta.o PetscSolver.o Petsc1DSolver.o Petsc2DSolver.o PetscSolverEtta.o GI.o GJ.o GK.o U.o V.o W.o Q.o JacobiSolverQ.o Delta.o output.o Topology.o CommunicationManager.o

obj_petsc_test= Main.o FlowField.o Simulation.o PetscZAZ.o PetscZAG.o TestRun.o Etta.o m.o M.o Dz.o Parameters.o AI_Inv.o AJ_Inv.o AK_Inv.o Solver.o JacobiSolverEtta.o ParallelJacobiSolverEtta.o PetscSolver.o Petsc1DSolver.o Petsc2DSolver.o  PetscSolverEtta.o GI.o GJ.o GK.o U.o V.o W.o Q.o JacobiSolverQ.o Delta.o output.o Topology.o CommunicationManager.o


all: nhsw nhsw_petsc test test_petsc

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -c -o $@ $<

nhsw: $(obj)
	$(CXX) $(CXXFLAGS) $(INC)  -o $@ $+ $(LIB)
	mkdir -p output

nhsw_petsc: $(obj_petsc)
	$(CXX) $(CXXFLAGS) $(INC)  -o $@ $+ $(LIB)
	mkdir -p output

test: $(obj_test)
	$(CXX) $(CXXFLAGS) $(INC)  -o $@ $+ $(LIB)
	mkdir -p output

test_petsc: $(obj_petsc_test)
	$(CXX) $(CXXFLAGS) $(INC)  -o $@ $+ $(LIB)
	mkdir -p output

test_run:
	rm -f output/*
	mpirun -n 4 ./test 10 10 6 3.5 0.01 1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 > output/log

test_run_petsc:
	rm -f output/*
	mpirun -n 4 ./test_petsc 10 10 6 3.5 0.01 1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 > output/log

run:
	rm -f output/*
	./nhsw 10 10 12 3.5 0.1 1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 > output/log
struct:
	rm -f output/*
	./nhsw 2 2 2 3.5 0.1 1 0.5 2.0 2.0 2.0 2.0 9.81 0.000001787 0 0 0 0 > output/log
oscilation:
	rm -f output/*
	./nhsw 20 20 24 3.5 0.01 1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 > output/log

dev: all
	rm -f output/*
	mpirun -n 1 ./test 4 4 6 3.5 0.01 1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0
	rm -f output/*
	mpirun -n 2 ./test 4 4 6 3.5 0.01 1 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0


clean:
	rm -f *.o core.*
	rm -f nhsw nhsw_petsc test test_petsc
	rm -rf output
clear:
	rm -f output/*
