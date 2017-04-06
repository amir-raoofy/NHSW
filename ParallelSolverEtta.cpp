#include "Simulation.h"
#include "Solver.h"

void Simulation::ParallelFirstStepUpdateEtta(){
	ParallelJacobiSolverEtta etta_solver(parameters_, flowField_, communicationManager_);
	etta_solver.SetParameters (0.00001,1000);
	etta_solver.solve();
}


