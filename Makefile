#CXX = g++
CXX = mpicxx
#CXX = mpiCC
CXXFLAGS = -Wall -std=c++11 -O3 -march=native -fopenmp
#CXXFLAGS = -g -O2 -qopt-report -Wall -std=c++11

#INC =-I.
#LIB =

# compile with opencl
#INC = -I/sccs/nvd/OpenCL/include/ -I.
#LIB = -L/sccs/nvd/ocl-icd/2.2.9/lib/ -lOpenCL -lm

#compile with petsc
INC = -I. $(PETSC_INC) ${PETSC_CC_INCLUDES}
LIB = $(PETSC_LIB)

obj= main.o FlowField.o Parameters.o Topology.o Simulation.o ParallelSimulation.o PetscSimulation.o Run.o Etta.o Delta.o m.o M.o Petsc1DSolverU.o Petsc1DSolverV.o PetscU.o PetscV.o U.o V.o W.o Dz.o Solver.o AI_Inv.o  AJ_Inv.o GI.o GJ.o GK.o zAz.o zAG.o PetscZAZ.o PetscZAG.o JacobiSolverEtta.o ParallelSolverEtta.o PetscSolverEtta.o ParallelJacobiSolverEtta.o output.o CommunicationManager.o PetscSolver.o Petsc1DSolver.o Petsc2DSolver.o TimeStep.o Scenario.o defaultScenario.o defaultScenarioInit.o defaultScenarioBoundaries.o


all: hsfs
	

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(LIB) -c -o $@ $<

hsfs: $(obj)
	$(CXX) $(CXXFLAGS) $(INC)  -o $@ $+ $(LIB)
	mkdir -p output

run:
	mpiexec -n 14 ./hsfs 28 28 10 1.0 200 0.005 0.5 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0 0 0.01 PARALLEL 0.001 1000 0.001 1000 1 2 > output/log.$(shell date +'%Y.%m.%d.%H.%M.%S')

clean:
	rm -f *.o core.*
	rm -f hsfs
	rm -rf output

clear:
	rm -f output/*
