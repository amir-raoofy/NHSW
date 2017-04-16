#include "PetscSimulation.h"
#include "Solver.h"

void PetscSimulation::UpdateEtta(){

	etta_solver_->set_time_step(time_step);
	etta_solver_->updateMat();
	etta_solver_->updateRHS();
	etta_solver_->solve();
	etta_solver_->updateField();

}

