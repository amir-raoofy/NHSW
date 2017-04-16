#include "PetscSimulation.h"
#include "Solver.h"

void PetscSimulation::UpdateEtta(){
	Petsc2DSolver etta_solver(parameters_, flowField_);
	etta_solver.set_time_step(time_step);
	etta_solver.updateMat();
	etta_solver.updateRHS();
	//etta_solver.SetParameters (0.00001,1000);
	etta_solver.solve();
	etta_solver.updateField();
}

