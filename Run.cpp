#include "Simulation.h" 
#include "Solver.h"

// TODO check the implementation of each function -> are the results correct?
//
void Simulation::Run(){
	InitEtta();
//	InitEttaBoundaries();
	Initm();
	InitM();
	InitU();
	InitV();
	InitW();
	InitQ();
	InitDzI();
	InitDzJ();
	InitzAz();
	InitGI();
	InitGJ();
	InitDelta();
	InitzAGI();
	InitzAGJ();	//TODO debug the solver to converge

	JacobiSolverEtta etta_solver(parameters_, flowField_);	//TODO implement the 2d solver
	etta_solver.solve();
}

//TODO make all the solvers members of Simulation
