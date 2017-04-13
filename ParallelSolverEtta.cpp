#include "Simulation.h"
#include "Solver.h"

void Simulation::ParallelUpdateEtta(){
	ParallelJacobiSolverEtta etta_solver(parameters_, flowField_, communicationManager_);
	etta_solver.SetParameters (0.00001,1000);
	etta_solver.set_time_step(time_step);
	etta_solver.solve();
}
